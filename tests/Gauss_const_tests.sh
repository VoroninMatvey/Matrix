#!/bin/bash

RESET='\033[0m'
BLUE='\033[0;34m'
RED='\033[31m'
GREEN='\033[0;32m'

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

tests_directory="${SCRIPT_DIR}/const_tests/Gauss/tests/"
answers_directory="${SCRIPT_DIR}/const_tests/Gauss/answers/"
determinant="${PROJECT_ROOT}/build/determination"
border=$(find ${tests_directory} -type f | wc -l)

echo ""
echo -e "${BLUE}Consts tests${RESET}"
for i in $(seq 1 1 ${border})
do
	work_answer=$(${determinant} < "${tests_directory}test${i}.txt")
	correct_answer=$(cat "${answers_directory}answ${i}.txt")
	echo -e "${BLUE}Test${i}${RESET}"
	echo "correct answer: ${correct_answer}"
	echo "work answer:    ${work_answer}"

	if [ "$correct_answer" = "$work_answer" ]; then
            echo -e "${GREEN}Test${i} passed${RESET}"
        else
            echo -e "${RED}Test${i} failed${RESET}"
        fi 

	echo ""
done 