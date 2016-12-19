from curses import wrapper

def main(stdscr):
	# clear screen
	stdscr.clear()

	# This raises ZeoDivisionError when i = 10.
	for i in range(0, 11):
		v = i-10
		stdscr.addstr(i, 0, '10 divied by {} is {}'.format(v, 10/v))

	stdscr.refresh()
	stdscr.getkey()

wrapper(main)
