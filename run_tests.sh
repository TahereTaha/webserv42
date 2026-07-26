#!/bin/zsh

tests=($(find test -name "*.test.run" ))

pids=()
i=1
for test in $tests ; do
	(
		if $test ; then
			echo "\033[32mSuccess\033[0m" at $test
		else  
			echo "\033[31mFailed\033[0m" at $test
		fi 
	) &
	pids[${i}]=$!
	i=$(echo $i '+' 1)
done
for pid in $pids; do
	wait $pid
done
echo 'done with all the tests'
