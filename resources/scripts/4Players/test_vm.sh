# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_vm.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clcreuso <clcreuso@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/12 19:03:24 by clcreuso          #+#    #+#              #
#    Updated: 2018/09/17 09:09:49 by mcarney          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
# **************************************************************************** #

NC='\033[0m'
RED='\033[0;31m'
GREEN='\033[0;32m'
FILES=$(ls -1 ./Champs)

if [ ! -d ./MCOREWAR_OUTPUT ]; then
	mkdir ./MCOREWAR_OUTPUT
fi

if [ ! -d ./RCOREWAR_OUTPUT ]; then
	mkdir ./RCOREWAR_OUTPUT
fi

if [[ $1 = "clean" ]]; then
	rm -rf ./corewar.dSYM
	rm -rf ./MY_LEAKS.output
	rm -rf ./RCOREWAR_OUTPUT
	rm -rf ./MCOREWAR_OUTPUT
	printf "The directories are cleared.\n"
	exit 1
fi

if [[ -z $1 ]] || ! echo $1 | egrep -q '^[0-9]+$' ; then
	printf "usage: sh $0 \"nb >= 0\" || \"clean\"\n"
	exit 0
fi

for P1 in $FILES
do

	NAME1=$(echo $P1 | rev | cut -c5- | rev)

	for P2 in $FILES
	do
		 # if [ $NAME1 == "Car" ]; then
	 	# 	break
	 	# fi
		NAME2=$(echo $P2 | rev | cut -c5- | rev)

		for P3 in $FILES
		do
			 # if [ $NAME1 == "Car" ]; then
			# 	break
			# fi
			NAME3=$(echo $P3 | rev | cut -c5- | rev)

			for P4 in $FILES
			do
				 # if [ $NAME1 == "Car" ]; then
				# 	break
				# fi
				NAME3=$(echo $P4 | rev | cut -c5- | rev)

				OUTPUT="${NAME1}_vs_${NAME2}_vs_${NAME3}_vs_${NAME4}.output"

				#                                                     LEAKS CHECK

				       # valgrind --leak-check=full --show-leak-kinds=all ./corewar ./Champs/$P1 ./Champs/$P2 -d $1 &> ./MCOREWAR_OUTPUT/$OUTPUT
				       # cat ./MCOREWAR_OUTPUT/$OUTPUT | sed 's/^=.*=//g' | grep -A 3 "definitely lost:" | column -t | fmt -c -w 75 > MY_LEAKS.output
				       # DIFF=$(diff ./MY_LEAKS.output ./GOOD_LEAKS.output)
				       # if [ "$DIFF" = "" ]; then
				       #     printf "${GREEN}$NAME1 VS $NAME2 ✔ ${NC}\n"
				       # else
				       #     printf "${RED}$NAME1 VS $NAME2 -> HAVE LEAKS ✘ ${NC}\n"
				       #     cat ./MY_LEAKS.output
				       #     read -p "Press any key to continue... " -n1 -s
				       #     printf "\n"
				       # fi

				#                                                      DIFF CHECK

				./corewar ./Champs/$P1 ./Champs/$P2 ./Champs/$P3 ./Champs/$P4 -dump $1 > ./MCOREWAR_OUTPUT/$OUTPUT
				./r_corewar ./Champs/$P1 ./Champs/$P2 ./Champs/$P3 ./Champs/$P4 -d $1 > ./RCOREWAR_OUTPUT/$OUTPUT

				DIFF=$(diff ./RCOREWAR_OUTPUT/$OUTPUT ./MCOREWAR_OUTPUT/$OUTPUT)

				if [ "$DIFF" = "" ]; then
					printf "${GREEN}$P1 VS $P2 VS $P3 VS $P4 ✔ ${NC}\n"
				else
					printf "${RED}$P1 VS $P2 VS $P3 VS $P4 ✘ (REAL COREWAR IN FIRST)${NC}\n"
					diff -d ./RCOREWAR_OUTPUT/$OUTPUT ./MCOREWAR_OUTPUT/$OUTPUT
					# read -p "Press any key to continue... " -n1 -s
					printf "\n"
				fi

			done

		done

	done

done
