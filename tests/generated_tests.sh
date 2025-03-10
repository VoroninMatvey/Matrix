#!/bin/bush

tests_directory='./matrix_data/tests/'
answers_directory='./matrix_data/answers/'
determinant='../determination'
border=$(find ${tests_directory} -type f | wc -l)

echo ""
echo -e "\e[32;1mGenerated tests\e[0m"
for i in $(seq 1 1 ${border})
do
	echo -e "\e[31mTest${i}\e[0m"
	echo "correct answer: $(cat "${answers_directory}answer${i}.txt")"
	echo "work answer: $(${determinant} < "${tests_directory}test${i}.txt")"
	echo ""
done
