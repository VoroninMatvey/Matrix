#!/bin/bush

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

tests_directory="${SCRIPT_DIR}/matrix_data/tests/"
answers_directory="${SCRIPT_DIR}/matrix_data/answers/"
determinant="${PROJECT_ROOT}/build/determination"
border=$(find ${tests_directory} -type f | wc -l)

echo ""
echo -e "\e[32;1mGenerated tests\e[0m"
for i in $(seq 1 1 ${border})
do
	echo -e "\e[31mTest${i}\e[0m"
	echo "correct answer: $(cat "${answers_directory}answer${i}.txt")"
	echo "work answer:    $(${determinant} < "${tests_directory}test${i}.txt")"
	echo ""
done
