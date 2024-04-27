set -e
trap "echo -e \"\nThere was an error :(\n\"" ERR

for arg in "$@"
do
	if [[ "$arg" == "build" ]]; 
	then 
		echo "Will build new program."
		build="1" 
	fi

	if [[ "$arg" == "run" ]];
	then 
		echo "Will run program."
		run="1" 
	fi	
	
	if [[ "$arg" == "debug" ]]; 
	then 
		echo "Debug flag set"
		debug="1" 
	fi
done


if [[ "$build"  -eq 1 ]];
then
	touch builderr.txt
	if [[ "$debug" -eq 1 ]]; 
	then
		cmake . -B build -DCMAKE_BUILD_TYPE=Debug 2> builderr.txt
	else
		cmake . -B build -DCMAKE_BUILD_TYPE=Release 2> builderr.txt
	fi
	make -C build 2> builderr.txt 
	
	echo "build worked."
	rm builderr.txt
fi

if [[ "$run" -eq 1 ]]; 
then
	touch runerr.txt
	if [[ "$debug" -eq 1 ]];
	then
		echo "Starting gdb debugger . . ."
		gdb ./bin/main
	else
		echo "Running main file . . ."
		./bin/main 2> runerr.txt
	fi
	rm runerr.txt
fi
exit 0
