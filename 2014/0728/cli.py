while True:
	str = raw_input("jimodb> ")
	if str :
		if str == "exit" or str == "exit;":
			print "Bye"
			break
		if ';' in str:
			print "========="
		else:
			print "---------"
		if str == "exit":
			break
