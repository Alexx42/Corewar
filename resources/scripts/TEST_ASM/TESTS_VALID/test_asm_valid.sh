#!/bin/sh ******************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    script_test_vm.sh                                .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/07/12 19:03:24 by clcreuso     #+#   ##    ##    #+#        #
#    Updated: 2018/07/24 22:02:13 by nbettach    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #


NC='\033[0m'
RED='\033[0;36m'
GREEN='\033[0;32m'
CHAMPS=$(ls -A1 ./CHAMPS)

if [ "$1" != "--clear" ] && [ "$1" != "" ]; then
	printf "usage: sh $0 [ --clear ]\n"
    exit 0
fi

if [ ! -d ./MCHAMPS ]; then
	mkdir ./MCHAMPS
fi

if [ ! -d ./RCHAMPS ]; then
	mkdir ./RCHAMPS
fi

if [ ! -d ./MASM_OUTPUT ]; then
	mkdir ./MASM_OUTPUT
fi

if [ ! -d ./RASM_OUTPUT ]; then
	mkdir ./RASM_OUTPUT
fi

if [[ $1 = "--clear" ]]; then
	rm -rf ./MCHAMPS
	rm -rf ./RCHAMPS
	rm -rf ./RASM_OUTPUT
	rm -rf ./MASM_OUTPUT
	rm -rf ./MY_LEAKS.output
	rm -rf ./asm.dSYM
	printf "The directories are cleared.\n"
	exit 1
fi

for P1 in $CHAMPS
do

	NAME1=$(echo $P1 | rev | cut -c3- | rev)

	OUTPUT="$NAME1.output"

	printf "\n%s\n" $P1 | fmt -c -w 75
	
	valgrind --leak-check=full --show-leak-kinds=all ./asm -v ./CHAMPS/"$P1" &> ./MASM_OUTPUT/"$NAME1.output"
	echo "\n---------------------------------- LEAKS ----------------------------------\n"
	cat ./MASM_OUTPUT/"$NAME1.output" | sed 's/^=.*=//g' | grep -A 3 "definitely lost:" | column -t | fmt -c -w 75 > MY_LEAKS.output
	if [ "$(diff ./MY_LEAKS.output ../GOOD_LEAKS.output)" != "" ]; then
		cat ./MY_LEAKS.output | fmt -c -w 75
	fi
	./asm ./CHAMPS/"$P1" &> ./MASM_OUTPUT/"$NAME1.output"
	mv ./CHAMPS/"$NAME1".cor ./MCHAMPS
	./r_asm ./CHAMPS/"$P1" &> ./RASM_OUTPUT/"$NAME1.output"
	mv ./CHAMPS/"$NAME1".cor ./RCHAMPS
	echo "\n------------------- DIFF BINARY (REAL COREWAR IN FIRST) -------------------\n"
	diff ./RCHAMPS/"$NAME1".cor ./MCHAMPS/"$NAME1".cor
	echo "\n------------------- DIFF OUTPUT (REAL COREWAR IN FIRST) -------------------"
	diff ./RASM_OUTPUT/"$NAME1.output" ./MASM_OUTPUT/"$NAME1.output"
	echo "\n----------------------------------- END -----------------------------------"
	# sleep 5
	
done
