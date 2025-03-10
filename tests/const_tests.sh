#!/bin/bush

tests_directory='./tests/const_tests/tests/'
answers_directory='./tests/const_tests/answers/'
determinant='./determination'
border=$(find ${tests_directory} -type f | wc -l)

echo ""
echo -e "\e[32;1mConsts tests\e[0m"
for i in $(seq 1 1 ${border})
do
	echo -e "\e[31mTest${i}\e[0m"
	echo "correct answer: $(cat "${answers_directory}answ${i}.txt")"
	echo "work answer:    $(${determinant} < "${tests_directory}test${i}.txt")"
	echo ""
done 
