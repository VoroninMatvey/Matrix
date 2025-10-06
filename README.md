# Calculating the discriminant matrix
## Information about project: in this project two methods for calculating the discriminant of a matrix were implemented: Gauss method and Bareiss method(for integer matrix)
## Building the project:
```
git clone git@github.com:VoroninMatvey/Matrix.git
cd Matrix
cmake -DCMAKE_BUILD_TYPE=Release -DINT_MATRIX=<ON/OFF> -S . -B build
cd build/
cmake --build .
```
Run the executable file:
```
./determination
```
The program accepts as input:
1) matrix size(count of rows or columns)
2) elem1 elem2 elem3 ...

Important: the matrix is read row by row

## Launching ready-made tests:
For Gauss:
```
bash ../tests/Gauss_const_tests.sh
```
For Bareiss:
```
bash ../tests/Bareiss_const_tests.sh
```

## Building the tests:
```
bash ../tests/generate_tests.sh
```
The sript accepts as input:
1) matrix size
2) maximum of determinant value
3) number of tests

In directory matrix_data are generated tests and answers

## Launching generated tests
```
bash ../tests/run_generated_tests.sh
```
