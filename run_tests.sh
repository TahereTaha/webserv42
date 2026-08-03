#!/bin/zsh

tests=($(find test -name "*.test.run" ))

pids=()
i=1
for test in $tests ; do
	(
		if $test ; then
			echo "\033[32mSuccess\033[0m" at $test ; exit 0
		else  
			echo "\033[31mFailed\033[0m" at $test ; exit 1
		fi 
	) &
	pids[${i}]=$!
	i=$(echo $i '+' 1)
done
errors=0
for pid in $pids; do
	wait $pid
	if [ $? -ne 0 ]; then
		errors=1
	fi
done
if [ $errors -ne 0 ]; then 
	echo "caught an error"
	exit 1
fi
echo 'done with all the tests'
