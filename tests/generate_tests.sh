#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"
GEN_DIR="${PROJECT_ROOT}/build/tests"

if [ $# -ne 3 ]; then
    echo "Usage: $0 <matrix_size> <max_determinant> <tests_number>"
    exit 1
fi

M_SIZE=$1
MAX_DET=$2
TESTS_NUMB=$3

echo -e "${M_SIZE}\n${MAX_DET}\n${TESTS_NUMB}" | "${GEN_DIR}/generator" "${PROJECT_ROOT}"