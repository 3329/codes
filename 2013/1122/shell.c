/*-----------------------------------------------------------------------------
 *
 * Copyright (C) 2000
 * Zykie Networks Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification is not permitted unless authorized in writing by a duly 
 * appointed officer of Zykie Networks Inc. or its derivatives
 *
 * Command Line Interface: Zykie Networks Shell
 *
 *---------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/param.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <sgtty.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <curses.h>
#include <pwd.h>
#include <fcntl.h>
#include <sys/shm.h>  
#include <click/app/proxy/proxy_shm.h>
#include "ca_util.h"
#include "ca_ui.h"
#include "node_sys.h"
#include "users.h"
#include "englog.h"
#include "getline/getline.h"
#include "version.h"
#include "feactl.h"

enum {N_CMD_NORMAL, N_CMD_KEEP, N_CMD_GET};
enum {USER_UNKNOWN, USER_TERMINAL, USER_WEB, USER_BATCH};

static void signal_eater(int);
static int set_conn(void);
static int data_to_output(char *buf, int len);
static int input_to_output(char *buf, int len);
static void check_sess(int signo);

static int recv_from_backend(int get_cmd_flag);
static int recv_from_stdin(void);
static int get_cmd_and_run(void);
static int stdin_readable_within_time(void);
static int shell_init(void);
static int shell_cleanup(void);
static void logon_msg(void);
static int is_conn_down(void);
static int stop_get(void);
static int check_conn_rc_state(int need_stop_get);
/*static int cli_enter_unix(void);*/

/* login message */
static char copyright_msg[] = 
"Copyright (c) 2009-2014 Zykie Networks Inc. All rights reserved.";

static char login_help[] = 
"Type \"?\" for available commands";

static int more_flag = TRUE; /*whether not need more functionality*/
static int stop_cmd_out = FALSE; /*whether or not user want to quit from more*/
static int display_msg = TRUE; /*whether the invalid license key msg needs to be displayed*/

static int sock_to_backend = -1;
static int conn_state = CONN_NORMAL;   /*init to be normal*/
static int stdin_state = CONN_NORMAL;

static int ui_type = USER_UNKNOWN; /*by default, the user input commands from terminal*/
/*the the user interface type is USER_TERMINAL, otherwise, is USER_WEBU*/

static int stdin_buf_index = 0;  /*stdin_buffer pointer*/
static char stdin_buff[MAX_LINE_SIZE + 1] = ""; /*string hold content from stdin*/
static char sock_buff[MAX_LINE_SIZE + 1] = "";  /*string hold content from backend*/

static session_state_t old_sess_state; /*keep old session state*/ 	


/* ----[ usage ]-------------------------------------------------------------
 *
 * Usage.
 */
static void
usage(void)
{
    printf("usage: ca_shell [-b]\n");
    printf("   -b: send command in batch mode.\n");
    return;
}


/* ----[ main ]--------------------------------------------------------------
 *
 * Main for the User Interface Frontend
 *
 */
int main(int argc, char *argv[])
{
    fd_set readfds;
    int maxfdp1;
    struct timeval sel_time;  /*time period for non-block select*/
    int rt; /*return value*/
    char ch;

    while ((ch = getopt(argc, argv, "b")) != -1) {
	switch (ch) {
	case 'b':    /*commands will be sent in batch mode*/
	    ui_type = USER_BATCH;
	    break;

	default:
	    usage();
	    exit(1);
	    break;
	}
    }

    /*get the current path*/
    get_cur_path(argv[0]);
 	
    /* display the logon message */
    logon_msg();

    /*do some initialization for cli*/
    shell_init();

    /*set the signals*/
    signal(SIGWINCH, get_scr_size);
    signal(SIGPIPE,signal_eater);	
    signal(SIGINT,signal_eater);
    signal(SIGABRT,signal_eater);
    signal(SIGQUIT,signal_eater);
    signal(SIGTSTP,signal_eater);

    /*init the select time period, maybe later can discard the sel_time*/
    sel_time.tv_sec = CONN_DOWN_TICKS;
    sel_time.tv_usec = 0;	
	while (1)
	{
		/*setup the connection to the right backend*/
		if (set_conn() < 0)
			return -1;

		conn_state = CONN_NORMAL;
		sess_state.ip = (local_node == host_node) ? ILOOPBACK : host_node->iaddr_dmz;
		sess_state.ip_cli = (local_node == host_node) ? ILOOPBACK : local_node->iaddr_dmz;
		sess_state.goto_node = FALSE; /*do not change any more*/
		/*send the init session to the backend let backend change*/
		/*its part*/
		if (send_user_session(sock_to_backend, &sess_state) < 0)
		{
			cli_englog_trace;
			conn_state = (conn_state == CONN_NORMAL) ? CONN_ERR : conn_state;
			continue;	   
		}

		FD_ZERO(&readfds);		
		/*inside the for loop, it is one session*/	
		for ( ; ; )
		{
			FD_SET((unsigned int)sock_to_backend,&readfds);
			FD_SET(STDIN_FILENO,&readfds);
			maxfdp1 = max(sock_to_backend,STDIN_FILENO) + 1;

			rt = select(maxfdp1,&readfds,NULL,NULL,&sel_time);
			if (rt < 0)
			{
				cli_englog_trace;
				conn_state = (conn_state == CONN_NORMAL) ? CONN_ERR : conn_state;  
				break;
			}		

			if (rt == 0) 
			{
				if (check_conn_rc_state(FALSE) >= 0)
					continue;
				else
					break;
			}

			/* Check if we have pending input from the socket,
			 * dump it to stdout, This would be a good place to 
			 * handle 'more' functionality
			 */		
			if (FD_ISSET((unsigned int)sock_to_backend,&readfds))
			{
				cli_englog_trace;
				if (read(sock_to_backend, NULL, 0) < 0)
				{
					cli_englog_trace;
					/*socket is dead*/
					conn_state = (conn_state == CONN_NORMAL) ? CONN_ERR : conn_state;  
					cli_englog_trace;
					break; /*exit the for loop*/
				}

				recv_from_backend(TRUE);
			}

			/* Check to see if we have stdin to pending, if so
			 * write it directly to the socket 
			 * the pending in is the typed text
			 */
			if (FD_ISSET(STDIN_FILENO,&readfds))
			{
				if (read(STDIN_FILENO, NULL, 0) < 0)
				{
					/*socket is dead*/
					stdin_state = (stdin_state == CONN_NORMAL) ? CONN_ERR : stdin_state;  
					cli_englog_trace;
					break; /*exit the for loop*/
				}

				recv_from_stdin();
			}

			fflush(null_fp);		    
			if ( (conn_state != CONN_NORMAL) ||
					( (stdin_state != CONN_NORMAL) && (ui_type != USER_BATCH)) )
				break;

		}/*for ( ; ; )*/

		if (conn_state == CONN_END) 
		{
			cli_englog_trace;
			shell_cleanup();
			break;
		}

		if (stdin_state == CONN_END)  
		{
			cli_englog_trace;

			/*get the output flushed if have some*/
			sleep(1);    /*wait this time for output flush from backend*/
			recv_from_backend(FALSE);	    

			shell_cleanup();
			break;
		}		

	}/* while (1) */

	return 0; 
}/*end of main*/




/****
 *   Functions for CA_SHELL
 */

static void signal_eater(int signo) {

	return;
}



/*check the connection to some node's backend, if not ok*/
/*change to local node or master node*/
static int set_conn(void)
{
	int i;
	int sock = -1;
	unsigned long ip_target; /*the target address to connect to*/ 
	/*by default, think the target can be found*/

	/*lock here later*/
	/*close the error socket*/
	cli_englog_trace;
	if ((conn_state == CONN_ERR) && (sock_to_backend > 0))
		close(sock_to_backend);

	/*try to find the target in the nodemap*/
	if (node_sn_to_order(sess_state.sn, &i) >= 0)
	{
		/*if local node, use loopback, else use inside ip*/
		if (i == 1)
			/*local node is always the first element in the Zykie*/
			/*here, index 1 means first since 0 is not used*/
			ip_target = ILOOPBACK;
		else
		{
			ip_target = cluster_node->nodes[i].iaddr_dmz;	    

			/*check whether or not local & remote ip duplicate*/
			/*local/cli side's inside ip duplicate*/
			/*also the remote ip can not be loopback!*/
			if ( (same_ip_num(local_node->iaddr_dmz) != 1) ||	    
					(same_ip_num(ip_target) != 1) ||		 
					(local_node->iaddr_dmz == ILOOPBACK) ||
					(ip_target == ILOOPBACK) )
				ip_target = 0;
		}	

		/*find the target, then try to connect to it*/
		if (ip_target != 0)
		{
			if (sock_and_conn(&sock, ip_target, CLI_PORT,  CONN_DOWN_TICKS) == 0)
			{
				/*set up new connection successfully*/
				if (conn_state == CONN_ERR)
					display_msg = FALSE;
				else
				{
					display_msg = TRUE;  /*display the new node's info for conn_new and conn_normal*/				     
					if (conn_state == CONN_NEW)
					{
						if (sock_to_backend != sock)
							close(sock_to_backend);  /*close the old socket*/	
					}
				}

				cli_englog_trace;
				sock_to_backend = sock;	
				set_sock_linger(sock_to_backend, 5);
				set_sock_reuse(sock_to_backend);	
				set_sock_keepalive(sock_to_backend);
				host_node = &(cluster_node->nodes[i]);
				return 0; /*connect to new host successfully*/
			}	
		}

		/*else can not connect to the host*/
		/*should continue for error handling*/	
	}

	/*come here, means either can not find target node or */
	/*connect to target node's backend failed*/
	switch (conn_state)
	{

		case CONN_NORMAL:
			/*must be the first time to connect to local backend*/
	/*printf("Local machine is not available. Please retry later.\n");*/
	printf("Loading configuration - please retry.\n");
	return -1;
	
    case CONN_NEW:
	
	/*connect to new node's backend failed*/
	/*go back to the old socket*/
	printf("Target machine is not available. No change.\n");
	memcpy((char *)&sess_state, (char *)&old_sess_state,
	       sizeof(session_state_t));
	    
	return 0;
	    
    case CONN_ERR:
	    
	/*try to connect to the local node*/
	/*already local backend?*/
	if (host_node == local_node)
	{
	    printf("Loading configuration - please retry.\n");
	    /*printf("Local machine is not available. Please retry later.\n");*/
	    return -1;
	}
	    
	/*try to connect to the local node's backend*/
	printf("Host machine is not available.\n");
	printf("Try to connect local machine......\n");
	    
	/*printf("Connect error , back to local backend. Please wait.\n");*/
	if (sock_and_conn(&sock, ILOOPBACK, CLI_PORT, CONN_DOWN_TICKS) < 0)
	{
	    printf("Loading configuration - please retry.\n");
	    /*printf("Local machine is not available. Please retry later.\n");*/
	    return -1;
	}
	    
	/*connect to local backend OK!*/
	sock_to_backend = sock;
	set_sock_linger(sock_to_backend, 5);
	set_sock_reuse(sock_to_backend);	
	set_sock_keepalive(sock_to_backend);	
	host_node = local_node;
	strncpy(sess_state.sn, local_node->sn, sizeof(sess_state.sn) - 1);
	    
	return 0;
	    
    case CONN_END:
	return -1;
	    
    default:
	return -1;
	    
    }/*for switch*/

    /*NOTREACHED*/
    return -1;
}
    
    
    
/*display result to output*/
static int data_to_output(char *buf, int len)
{
    int i;
    
    if (ui_type != USER_TERMINAL)
    {
	/*for web user*/
	for (i = 0; i < len; i++)
	{
	    if (buf[i] != (char)F_EOP)
		write(STDOUT_FILENO, &(buf[i]), 1);
	}
    }
    else
    {
	/*for terminal*/
	/*internally, page_line > 255 means no page feature*/
	if ( (!more_flag) || (sess_state.page_line > 255) )
	    write(STDOUT_FILENO, buf, len);
	else
	{
	    for ( i = 0; i < len; i++)
	    {
		if (stop_cmd_out)
		    break;
		
		/*==1 means stop output*/
		if (more_write(&buf[i], 1, sess_state.page_line) == 1)
		    stop_cmd_out = TRUE;
	    }
	}
    }

    /*flush data in all the descriptors*/
    fflush(null_fp);
    return 0;    
}	


/*echo input to output*/
static int input_to_output(char *buf, int len)
{
    if ( (ui_type == USER_TERMINAL) ||
	 (ui_type == USER_BATCH) )
	write(STDOUT_FILENO, buf, len);

    fflush(null_fp);
    return 0;    
}	



static int stop_get(void)
{
    if (ui_type == USER_TERMINAL)
	send_key(STDIN_FILENO, '\032');

    return 0;
}

/*check whether or not the current session should stay in */
/*config mode any longer if the current state is config */
static void check_sess(int signo)
{
    int errno_saved;
    
    errno_saved = errno;

    /*check the connection*/
    if (check_conn_rc_state(TRUE) >= 0)    
	local_node->sess_conf_quiet_ticks += ONE_TICK;
    
    /*if backend has data, read the data, but ignore the delay flag*/
    recv_from_backend(FALSE);

    errno = errno_saved;
    return;
}


static int get_cmd_and_run(void)
{
    static int tell_next_cmd = N_CMD_NORMAL; /*what should next command should be*/
    char *input, *pos;
    unsigned int count;
    int is_hist_cmd = TRUE;
    static char scmd[MAX_LINE_SIZE + 1] = "";  /*string hold the new command*/
    char sstate[MAX_TOKEN_SIZE + 1] = "";
    char *prompt;
       
    /*set the prompt*/    
    set_prompt(sock_buff, sizeof(sock_buff) - 1);
    prompt = sock_buff;

    /*check whether or not there are rest command*/
    switch  (tell_next_cmd)
    {
    case N_CMD_KEEP:
	
	pos = strrchr(scmd, '?');
	if (pos != NULL)
	    *pos = 0;
	
	break;	
	
    case N_CMD_GET:
	
	memset(scmd, 0, sizeof(scmd));
	strncpy(scmd, sess_state.next_cmd, sizeof(scmd) - 1);
	
	ltrim(scmd);
	rtrim(scmd);
	count = strlen(scmd);
	if ((count > 0)  && 
	    (count < sizeof(scmd) - 2) )
	{
	    scmd[count] = ' ';
	    scmd[count + 1] = '\0';
	}
	
	pos = strchr(scmd, '\n');
	if (pos != NULL)
	    *pos = 0;
		
	break;
	
    default:
	
	memset(scmd, 0, sizeof(scmd));
	break;
    }
    
    /*clear sess_state.next_cmd*/
    memset(sess_state.next_cmd, 0, sizeof(sess_state.next_cmd));
    
    /*open the alrm signal here, before getline*/
    set_timer_func(ONE_TICK, check_sess);
    
    /*get control info from previous command*/
    if (ui_type == USER_TERMINAL)
    {
	if (!is_block_fd(STDIN_FILENO))
	{
	    /*for debug*/
	    cli_englog_trace;
	    englog(ENGLOG_CLI, CLI_SYS_ERR,"For some reason, stdin becomes non-block!");

	    block_fd(STDIN_FILENO);
	}
	
	/*get the input*/	
	input = getline(prompt, scmd);

	/*copy the command to scmd*/
	memset(scmd, 0, sizeof(scmd));
	if (input != NULL)
	{
	    count = strlen(input);
	    if (count > MAX_LINE_SIZE)
	    {
		printf("Too long a line(> %u characters).\n", MAX_LINE_SIZE);
		unset_timer_func();
		/*after get a command, reset the idle timer*/
		if (sess_state.acc_level >= CLI_LEVEL_CONFIG)
		    local_node->sess_conf_quiet_ticks = 0;		    

		return -1;
	    }
	    else
	    {
		strncpy(scmd, input, sizeof(scmd) - 1); 
		scmd[count] = 0;
	    }
	}
    }
    else
    {
	/*for webui*/
	cli_englog_trace;

	if (ui_type == USER_WEB)
	    putchar((char)F_EOP);
	else
	    printf("%s", prompt);   /*must be in the batch mode, need print prompt*/

	memset(scmd, 0, sizeof(scmd));
	input = fgets(scmd, sizeof(scmd), stdin);
	/*if no input or no newline, assume the input has someting wrong*/
	if ((input == NULL)  ||
	    ((strchr(scmd, '\n') == NULL) && (ui_type != USER_BATCH)))
	{
	    cli_englog_trace;
	    stdin_state = CONN_END;
	    unset_timer_func();
	    if (sess_state.acc_level >= CLI_LEVEL_CONFIG)
		local_node->sess_conf_quiet_ticks = 0;
	    
	    return -1;
	}
	
	/*if no new line, add one for batch mode*/
	count = strlen(scmd);
	if ( (ui_type == USER_BATCH) && 
	     (strchr(scmd, '\n') == NULL) )
	    snprintf(scmd + count, sizeof(scmd) - count, " \n");
    }

    /*ignore the sigalrm signal after get a command*/
    unset_timer_func();
    
    /*since get a command, should re-set the idle timer*/
    if (sess_state.acc_level >= CLI_LEVEL_CONFIG)
	local_node->sess_conf_quiet_ticks = 0;
    
    /*get rid of leading and following blanks*/
    ltrim(scmd);
    rtrim(scmd);
    
    /*normally next command is N_CMD_NORMAL*/
    tell_next_cmd = N_CMD_NORMAL;		
    count = strlen(scmd);
    
    /*empty command*/
    if (count <= 1) 
	return -1;

    /*last char must be newline*/
    if (scmd[count - 1] != '\n')
	return -1;	

    /*beginning with a '#' is comment, ignore it*/
    if (scmd[0] == '#')
	return -1;

    if ( (scmd[count - 2] == '?') && 
	 (num_of_char(scmd, '"', strlen(scmd)) % 2 == 0) )
	tell_next_cmd = N_CMD_KEEP;
    
    if (scmd[count - 2] == '\t')
    {
	if (count > 2)
	    tell_next_cmd = N_CMD_GET;
	else
	    return -1; /*only '\t\n' not a command*/
    }
        
    /*^z*/
    if (scmd[count - 2] == '\032')
    {
	is_hist_cmd = FALSE;
	memset(scmd, 0, sizeof(scmd));
	if (sess_state.acc_level >= CLI_LEVEL_CONFIG)
	    strcpy(scmd, "exit \n");
	else
	    strcpy(scmd, "\n");	    
    }
    
    /*webui and "mode?" command*/
    if ( (strncmp(scmd, "mode?", 5) == 0) &&
	 (ui_type != USER_TERMINAL) )
    {
	memset(sstate, 0, sizeof(sstate));
	get_sess_state_str(sess_state.acc_level, sstate);
	write(STDOUT_FILENO, sstate, strlen(sstate));
	putchar('\n');
	return -1;
    }

#if 0
    /*for unix shell*/
    if ( (ui_type == USER_TERMINAL) &&
	 (sess_state.acc_level == CLI_LEVEL_ENGINEER) &&
	 (strncmp(scmd, "tcsh", 4) == 0))
    {
	cli_enter_unix();
	putchar('\n');
	return -1;
    }
#endif

    /*send the command to the backend*/
    /*do the check on write is also important*/
    if (send_user_cmd(sock_to_backend, scmd) < 0)
    {
	cli_englog_trace;
   	conn_state = (conn_state == CONN_NORMAL) ? CONN_ERR : conn_state;
	if (conn_state == CONN_ERR)
	    printf("connection to host machine is lost. Try to re-connect. \n"
		   "Command not sent.\n");
    }
	
    /* Add the command , and only the command */
    if (is_hist_cmd)
    {
	if (scmd[count - 2] == '\t')
	{
	    scmd[count - 1] = 0;
	    scmd[count - 2] = 0;
	    scmd[count - 3] = '\n';
	}

	gl_histadd(scmd);	
    }

    return 0;        
}


static int stdin_readable_within_time(void)
{
    int rt;

    /*has already sent the "quit" command*/
    if (stdin_state == CONN_END)
	return -1;

    do 
    {
	 /*set errno = 0, for interrupted select system call*/
	errno = 0;   
	rt = readable_within_time(STDIN_FILENO, 0, T_TERM);

    } while ( (rt < 0) && (errno == EINTR));

    if (rt < 0)
    {
	cli_englog_trace;	

	/*if in batch mode, send all the pending read buf and add a new line to the backend*/
	if (ui_type == USER_BATCH) {

	    stdin_buff[stdin_buf_index] = '\n';
	    input_to_output("\n", 1);
	    
	    /*this is block write*/
	    write(sock_to_backend, stdin_buff, stdin_buf_index+1);   
	}

	/*send "quit" command to the backend*/    
	/*the first newline is to gurantee the previous command end gracefully*/
	/*the second newline is for "quit" command*/
	/*no need to check the result of send_user_cmd() here since no need to re-connect*/
	send_user_cmd(sock_to_backend, " \nquit \n");
	stdin_state = CONN_END;			

	/*means to flush the data in all the descriptors*/
	fflush(null_fp);	    
    }
	    
    return rt;
}


static int recv_from_backend(int get_cmd_flag)
{
    static int is_next_ctl = FALSE;  /*whether or not the next char is a control flag*/    
    int is_delay_cmd;
    char ch = '\0';
    char *no_display;
    int count = 0;
    int no_read = FALSE;
    int rt;
    
    cli_englog_trace;
    while (conn_state == CONN_NORMAL)
    {
	if (no_read)
	    no_read = FALSE;
	else
	{
	    rt = readable_within_time(sock_to_backend, 0, T_SOCK);
	    if (rt < 0)
	    {
		/*dead connection to backend*/
		cli_englog_trace;
		conn_state = (conn_state == CONN_NORMAL) ? CONN_ERR : conn_state;   /*connection is lost*/
		break;
	    }
	    
	    if (rt == 0)
	    {
		cli_englog_trace;
		break; /*no data from backend socket*/	
	    }

	    if (read(sock_to_backend, &ch, 1) != 1)
	    {
		cli_englog_trace;
		conn_state = (conn_state == CONN_NORMAL) ? CONN_ERR : conn_state;   /*connection is lost*/
		break;
	    }
	}
	
	if (ch == (char)F_CTL_START)
	{
	    /*check if the real beginning of a control char*/
	    /*defect: do not know error is connection lost or not stuff key*/
	    /*later, need to make out*/
	    if (recv_stuff_key(sock_to_backend, sock_buff, &count) == 0)
	    {
		cli_englog_trace;
		
		/*real begin of a special char*/
		/*need to print out whatever get*/
		is_next_ctl = TRUE;		
	    }
	    else
	    {
		/*not the real begin of a special char*/
		/*need to print out whatever get*/
		/*output the first F_CTL_START, might useful output*/
		data_to_output(&ch, 1);
		
		/*to see whether in recv_stuff_key, a F_CTL_START is read out*/
		/*if yes, keep this F_CTL_START for next stuff key check*/
		if (count > 0)
		{
		    if (sock_buff[count - 1] != (char)F_CTL_START)
			data_to_output(sock_buff, count);
		    else
		    {
			ch = (char)F_CTL_START;
			data_to_output(sock_buff, count - 1);
			no_read = TRUE; /*keep the F_CTL_START flag*/
		    }
		}
		
		/*clear input buff is because if send a line without '\n'*/
		/*backend will not how to do with it*/
		stdin_buf_index = 0;
		is_next_ctl = FALSE;		
	    }
	    
	    continue; /*to get next character*/
	}
	
	if (!is_next_ctl)
	{
	    /*come here means this char is a normal char, not control char*/
	    data_to_output(&ch, 1);		
	    stdin_buf_index = 0; /*clear the buffer*/			
	}
	else	    
	{		
	    /*this is control char handle part, first set the is_next_ctl*/
	    /*flag to be 0, means next char will be normal char again!*/
	    is_next_ctl = FALSE;
	    /*this char is control character!*/
	    switch (ch)
	    {
		
	    case (char)F_BOP:
		cli_englog_trace;
		
		/*beginning of prompt handling*/
		/*for prompt*/
		if (recv_prompt(sock_to_backend, sock_buff, &is_delay_cmd) < 0)
		{
		    conn_state = (conn_state == CONN_NORMAL) ? CONN_ERR : conn_state;   /*connection is lost*/
		    /*if (conn_state == CONN_ERR)
		      printf("connection to host machine is lost! Try to re-connect. \n");		       */
		}		    
		else
		{			
		    /*for terminal user, add a new line so that the prompt*/
		    /*will start from a new line*/
		    if (ui_type == USER_TERMINAL)
			data_to_output("\n", 1);
		    
		    if (!is_delay_cmd)
		    {
			/*get the next command and run*/
			stop_cmd_out = FALSE;
			init_scr();
			
			cli_englog_trace;
			/*read until get and run a valid command*/
			if (get_cmd_flag) {

			    while ( (get_cmd_and_run() < 0) &&
				(stdin_state == CONN_NORMAL) );				      
			}
		    }
		    else
		    {
			/*for debug*/
			cli_englog_trace;
			englog(ENGLOG_CLI, CLI_CMD_INFO,"get a delay command feedback from backend!");

			stop_cmd_out = FALSE;
			/*output the prompt*/
			if ( (ui_type == USER_TERMINAL) ||
			     (ui_type == USER_BATCH) )
			    data_to_output(sock_buff, strlen(sock_buff));

			stdin_buf_index = 0; /*clear the buffer*/
		    }
		}
		    
		break;
		    
	    case (char)F_BOS:
		cli_englog_trace;
		    
		/*copy the old session state*/
		memcpy((char *)&old_sess_state, (char *)&sess_state,
		       sizeof(session_state_t));
		    
		if (recv_user_session(sock_to_backend, &sess_state, 0) < 0)
		{
		    cli_englog_trace;
		    conn_state = (conn_state == CONN_NORMAL) ? CONN_ERR : conn_state;   /*connection is lost*/		    
		}
		else
		{				
		    /*check the new session state info*/
		    /*if cli can get the sess_state info, must be tonode or tomaster*/
		    /*command, but can not ip inside command!*/
		    if (sess_state.goto_node == TRUE)
			conn_state = CONN_NEW;
			
		    if (sess_state.acc_level == CLI_LEVEL_LOG)
			conn_state = CONN_END;
		    			
		    if ((old_sess_state.acc_level < CLI_LEVEL_CONFIG) &&
			(sess_state.acc_level >= CLI_LEVEL_CONFIG))
		    {
			/*get the permission to enter config mode*/
			local_node_private->sess_conf_id = getpid();
			local_node->sess_conf_start_time = sess_state.sess_conf_start_time;
			local_node->sess_conf_quiet_ticks = 0;
			cluster->sess_conf_start_time = sess_state.sess_conf_start_time;	
		    }
		    
		    if ((old_sess_state.acc_level >= CLI_LEVEL_CONFIG) &&
			(sess_state.acc_level < CLI_LEVEL_CONFIG))
		    {
			if (local_node_private->sess_conf_id == getpid())
			{
			    local_node_private->sess_conf_id = 0;
			    local_node->sess_conf_start_time = 0;
			}
		    }
		}				 
		break;

	    case (char)F_BOC:
		cli_englog_trace;

		/*delayed command, should be put into history*/
		memset(sock_buff, 0, sizeof(sock_buff));
		if (recv_user_cmd(sock_to_backend, sock_buff) < 0)
		{
		    conn_state = (conn_state == CONN_NORMAL) ? CONN_ERR : conn_state;
		    /*if (conn_state == CONN_ERR)
		      printf("connection to host machine is lost! Try to re-connect. \n");		       */
		}
		else
		{
		    /*add to history*/
		    gl_histadd(sock_buff);
		    if (ui_type == USER_TERMINAL)
			data_to_output(sock_buff, strlen(sock_buff));
		}
		break;

	    case (char)F_PASS:
		/*cli_englog_trace*/
		
		/*for webui, the password has already been sent*/
		if (ui_type == USER_TERMINAL)
		{
		    no_display = getpass("");/*password is saved in a static string*/
		    /*with size _PASSWORD_LEN*/
		    if (write(sock_to_backend, no_display, strlen(no_display)) < 0)
		    {
			cli_englog_trace;
			conn_state = (conn_state == CONN_NORMAL) ? CONN_ERR : conn_state;
			if (conn_state == CONN_ERR)
			    printf("connection to host machine is lost. Try to re-connect. \n"
				   "Data not sent.\n");	       
			
		    }
		    else
		    {
			if (write(sock_to_backend, "\n", 1) < 0)
			{
			    conn_state = (conn_state == CONN_NORMAL) ? CONN_ERR : conn_state;
			    if (conn_state == CONN_ERR)
				printf("connection to host machine is lost. Try to re-connect. \n"
				       "Data not sent.\n");		       
			}
		    }
		    memset(no_display, 0, _PASSWORD_LEN);
		}
		break;

	    case (char)F_MSG:  /*to print some common, global message*/
		
		if (display_msg)
		{
		    if (ui_type == USER_TERMINAL)
		    {
			printf("%s", S_LIC_KEY);
			show_contact_fc();
		    }
		}
				
		break;
		
	    case (char)F_END:
		cli_englog_trace;
		
		conn_state = CONN_END;				
		stdin_state = CONN_END;
		break;						

	    case (char)F_BOD:
		/*for each command, by default, more is needed*/
		more_flag = TRUE;
		break;

	    case (char)F_MORE:
		init_scr();
		more_flag = TRUE;
		break;

	    case (char)F_NON_MORE:
		stop_cmd_out = FALSE;
		more_flag = FALSE;
		break;

	    default:
		
		/*in fact not a special char, must be the user*/
		/*output happens to be same as our key magic string!*/
		data_to_output(&ch, 1);		
		stdin_buf_index = 0; /*clear the buffer*/			
		break;
	    }  /*for switch*/
	}/*for is_next_ctl's else*/	    
    }/*for while*/
	
    return 0;    
}
    
    
static int recv_from_stdin(void)
{
    char ch;
    
    /*initialize the screen*/
    init_scr();
    
    while ( (stdin_readable_within_time() > 0) &&
	    (stdin_state == CONN_NORMAL) &&
	    (conn_state == CONN_NORMAL) )
    {
	if (ui_type == USER_TERMINAL)
	    ch = gl_getwc();
	else
	    ch = fgetc(stdin);
	
	switch (ch)
	{
	    /*case '\032':*/
	case '\003':   /*^c*/
	    cli_englog_trace;
	    if (send(sock_to_backend, "\003", 1, MSG_OOB) < 0)
		conn_state = (conn_state == CONN_NORMAL) ? CONN_ERR : conn_state;

#if 0
	    /*close socket and reset connect state*/
	    /*we can not close the socket directly, because a lot of backend command*/
	    /*can not be killed!*/
	    close(sock_to_backend);
	    conn_state = (conn_state == CONN_NORMAL) ? CONN_ERR : conn_state;
#endif

	    break;
	    
	case '\n': 
	case '\r':
	    cli_englog_trace;
	    stdin_buff[stdin_buf_index] = '\n';
	    input_to_output("\n", 1);
	    
	    /*this is block write*/
	    if (write(sock_to_backend, stdin_buff, stdin_buf_index+1) < 0)
	    {
		conn_state = (conn_state == CONN_NORMAL) ? CONN_ERR : conn_state;
		if (conn_state == CONN_ERR)
		    printf("connection to host machine is lost. Try to re-connect. \n"
			   "Data not sent.\n");		       
	    }
	    
	    /*means to flush the data in all the descriptors*/
	    fflush(null_fp);
	    stdin_buf_index = 0;
	    break;
	    
	case '\b':
	    if (stdin_buf_index > 0)
	    {
		stdin_buf_index--;
		input_to_output("\b \b", 3);
	    }
	    break;
	    
	default:
	    if (isprint(ch) || isspace(ch))
	    {
		stdin_buff[stdin_buf_index] = ch;
		stdin_buf_index++;
		input_to_output(&ch, 1);	
	    }				
	    break;	    
	}
	
	if (stdin_buf_index > MAX_LINE_SIZE)
	{
	    stdin_buf_index = 0;
	    printf("\nToo long a line.\n");
	}
    }
        
    return 0;
}


/*MY_PRODUCT and MY_VERSION are defined in version.h*/ 
static void logon_msg(void)
{
    printf("%s %s\n", MY_PRODUCT, MY_VERSION);
    printf("%s\n", copyright_msg);
    printf("\n%s\n\n", login_help);
}


/*now cli will not be responsible for starting backend*/
/*if it is not there*/
static int shell_init(void)
{
    /*lock here later*/
    /*set stdin, stdout buffer*/
    zero_std_buf();    
    
    /*initialize the shared memory info*/
    /*use a for loop to get the share memory id, waiting noded*/
    for ( ; ; )
    {
	 clu_shm_id = shmget(CLU_SHM_KEY, CLU_SHM_SIZE, CLU_SHM_MODE);
	 if (clu_shm_id > 0)
	     break;

	 sleep(1);
    }           
   
    /*attach to the pre-created shared memory by noded*/
    /*since this is a must, just use a loop to do attach*/
    for ( ; ; )
    {
	cluster_node = shmat(clu_shm_id, 0, 0);
	if (cluster_node != (void *) -1)
	    break;
	
	sleep(1); /*wait for noded*/
    }
    
    /*set global variables*/
    cluster = &(cluster_node->cluster);
    local_node_private = &(cluster_node->node_private);	
    local_node = &(cluster_node->nodes[1]);
    host_node = local_node;
    
    /*set the terminal mode and signals*/
    if (ui_type == USER_UNKNOWN)
    {
	/*find the user type*/
	if (isatty(STDIN_FILENO))
	{
	    ui_type = USER_TERMINAL;
	    set_term_mode();
	}    
	else
	    ui_type = USER_WEB;
    }
    
    /*set the default session*/
    init_user_session(&sess_state);	
    get_account(sess_state.account, sess_state.passwd); 
    
    return 0;    
}


static int shell_cleanup(void)
{
    /*print the last newline*/
    printf("\n");

    /*check config mode*/
    if (local_node_private->sess_conf_id == getpid())
    {
	local_node_private->sess_conf_id = 0;
	local_node->sess_conf_start_time = 0;
    }

    /*send end flag to the backend and close socket*/    
    send_ctl_flag(sock_to_backend, F_END);
    close(sock_to_backend);

    /*handle the stdin case for non-terminal*/
    if ((ui_type != USER_TERMINAL) &&
	(ui_type != USER_BATCH) )
    {
	putchar((char)F_EOP);		    
	close(STDIN_FILENO);
    }    

    /*detach the shared memory*/
    if (shmdt(cluster_node) < 0)
	ui_englog_error(ENGLOG_CLI, CLI_SYS_ERR, "Detach global var: cluster"); 

    return 0;
}


/*whether or not the cli-backend tcp connection is down due to address change*/
/*1 means down, 0 means not down, come here, host_node must be OK!*/
static int is_conn_down(void)
{
    /*local session, never down*/
    if (local_node != host_node)
    {
	/*local/cli side change ip address*/
	if (sess_state.ip_cli != local_node->iaddr_dmz) 
	    return TRUE;

	/*local/cli side's inside ip duplicate*/
	if (same_ip_num(sess_state.ip_cli) != 1)
	    return TRUE;	
	
	/*host node ip can not be loopback!*/
	if (sess_state.ip == ILOOPBACK)
	    return TRUE;	

	/*host/backend side change ip address*/
	if (sess_state.ip != host_node->iaddr_dmz)
	    return TRUE;	

	/*host/backend side's inside ip duplicate*/
	if (same_ip_num(sess_state.ip) != 1)
	    return TRUE;	
    }

    return FALSE;
}



/*check  1.rc:  the cli and backend are still in the same real cluster*/
/*       2.conn:  whether the connection between the cli and machine is still OK*/
/*       3.state:  some abnormal event make the session in the wrong mode */
/* return -1 means need to setup new connection, otherwise return 0*/
static int check_conn_rc_state(int need_stop_get)
{
    int i;

    /*1. the cli and backend are still in the same real cluster*/
    if (node_sn_to_order(sess_state.sn, &i) < 0)
    {	 
	cli_englog_trace;
	englog(ENGLOG_CLI, CLI_SESS_INFO, 
	       "The backend and cli are not in the same real cluster. \n");
	
	/*key in ctrl+z to jump out of get command*/
	if (need_stop_get)
	    stop_get();
	
	/*printf the message, since set_conn() has messages, no need to print*/
	/*set conn_state to be error*/
	conn_state = (conn_state == CONN_NORMAL)? CONN_ERR:conn_state;		
	return -1;
    }

    /*2. whether the connection between the cli and backend is still OK*/
    if (is_conn_down())
    {
	cli_englog_trace;
	englog(ENGLOG_CLI, CLI_SESS_INFO, 
	       "The host or local node changed the IP address.");
	
	/*key in ctrl+z to jump out of get command*/
	if (need_stop_get)
	    stop_get();
	
	/*printf the message*/
	printf("Connection to backend is lost. Try to re-connect. \n");

	/*set conn_state to be error*/
	conn_state = (conn_state == CONN_NORMAL)? CONN_ERR:conn_state;		
	return -1;
    }    

    /*if not in config mode, should not hold the lock*/
    if ( sess_state.acc_level < CLI_LEVEL_CONFIG) 	 
    {
	/*if the sess_conf_id == getpid(), it must*/
	/*be some synchronization problem, set*/
	/*the id and time to be 0*/
	if (local_node_private->sess_conf_id == getpid())
	{
	    cli_englog_trace;
	    englog(ENGLOG_CLI, CLI_SESS_INFO, "Should not in config mode");		
	    local_node_private->sess_conf_id = 0;
	    local_node->sess_conf_start_time = 0;
	}
    }    
    else
    {    
	/*3. should keep in config/engineer mode?*/
	if ( (!is_sess_conf(sess_state.sess_conf_start_time)) ||
	     (local_node_private->sess_conf_id != getpid()) ||
	     (host_node->status != MASTER) )	 
	{
	    
	    /*key in ctrl+z*/	
	    cli_englog_trace;
	    if (need_stop_get)
	    {
		stop_get();
		
		if (sess_state.acc_level == CLI_LEVEL_ENGINEER)
		{
		    if (local_node->sess_conf_quiet_ticks > cluster->sess_conf_timeout)
			/*print warning message and send exit command to backend*/
			printf("\n*** Idle time > %u seconds. No longer in engineer mode. ***\n\n", 
			       cluster->sess_conf_timeout);
		    else
			/*this session is not config mode any more due to long idle time*/
			printf("\n***System is busy! No longer in engineer mode. ***\n\n");				 
		}
		else
		{
		    if (local_node->sess_conf_quiet_ticks > cluster->sess_conf_timeout)
			/*print warning message and send exit command to backend*/
			printf("\n*** Idle time > %u seconds. No longer in config mode. ***\n\n", 
			       cluster->sess_conf_timeout);
		    else
		    /*this session is not config mode any more due to long idle time*/
			printf("\n***System is busy. No longer in config mode. ***\n\n");
		}
		
		/*drop the user level*/
		sess_state.acc_level = CLI_LEVEL_ENABLE;
		send_user_session(sock_to_backend, &sess_state);
		
		local_node->sess_conf_quiet_ticks = 0;	
	    }
	}
    }

    return 0;
}



#if 0

#define ROOT_PASSWD   "click1"
static int cli_enter_unix(void)
{ 
#if 0
    char *passwd;

    /*check the root password*/
    passwd = getpass("Root password:");
    if (passwd == NULL)
    {
	printf("Can't get password from input.\n");	
	return -1;
    }

    if (strcmp(passwd, ROOT_PASSWD) != 0)
    {
	printf("Fail to enter unix shell. Bad password.\n");	
	return -1;
    }

    system("/bin/tcsh -i");
#endif

    system("/usr/bin/su -");
    return 0;
}

#endif











