# !/usr/bin/env pyhton
# coding: utf-8  
#
# Created by Young, 2015/02/13
# Description:
#   Use ftp get remote files.


from ftplib import FTP 
 

def ftp_up(filename = "20120904.rar"): 
    ftp=FTP() 
    ftp.set_debuglevel(2)#打开调试级别2，显示详细信息;0为关闭调试信息 
    ftp.connect('192.168.0.1','21')#连接 
    ftp.login('admin','admin')#登录，如果匿名登录则用空串代替即可 
    #print ftp.getwelcome()#显示ftp服务器欢迎信息 
    #ftp.cwd('xxx/xxx/') #选择操作目录 
    bufsize = 1024#设置缓冲块大小 
    file_handler = open(filename,'rb')#以读模式在本地打开文件 
    ftp.storbinary('STOR %s' % os.path.basename(filename),file_handler,bufsize)#上传文件 
    ftp.set_debuglevel(0) 
    file_handler.close() 
    ftp.quit() 
    print "ftp up OK" 
 
def ftp_down(filename = "20120904.rar"): 
    ftp=FTP() 
    ftp.set_debuglevel(2) 
    ftp.connect('192.168.0.1','21') 
    ftp.login('admin','admin') 
    #print ftp.getwelcome()#显示ftp服务器欢迎信息 
    #ftp.cwd('xxx/xxx/') #选择操作目录 
    bufsize = 1024 
    filename = "20120904.rar" 
    file_handler = open(filename,'wb').write #以写模式在本地打开文件 
    ftp.retrbinary('RETR %s' % os.path.basename(filename),file_handler,bufsize)#接收服务器上文件并写入本地文件 
    ftp.set_debuglevel(0) 
    file_handler.close() 
    ftp.quit() 
    print "ftp down OK" 
