#!/bin/bash
#http://linuxpixies.blogspot.jp/2011/06/tmux-copy-mode-and-how-to-control.html


starttmux() { 
	tmux new-session -d -s $sessionname 
	for i in "${Exes[@]}"
	do 
		num=`pgrep -u ${USER} $i|wc -l`
		for ((n=1; n<=${num}; n++))
		do
			pid=`pgrep -u ${USER} $i|sed -n ${n}p`
			source_txt="source_"${i}"_"${n}".txt"
			echo "attach $pid" > $source_txt
			#echo "b alarm.c:50" >> $source_txt
			echo "c" >> $source_txt
			tmux split-window -v "gdb -x $source_txt"                                 
			tmux select-layout tiled
		done
	done

	tmux attach -t $sessionname 
}


Exes=(test.exe)
sessionname=$1
starttmux



