# Calculating the discriminant matrix
## Information about project: in this project two methods for calculating the discriminant of a matrix were implemented: Gauss method and Bareiss method(for integer matrix)
## Building the project:

```
git clone git@github.com:VoroninMatvey/Matrix.git
cd Matrix
make
```

Run executable file:
```
./determination
```

The program accepts as input:
1)matrix size(count of rows or columns)
2)elem1 elem2 elem3 ...
Moreover, the matrix is read row by row

#Launching ready-made tests:

```
bash tests/const_tests.sh
```

# Building the tests:

```
cd tests
make
./generator 
```
The program accepts as input:
1)matrix size
2)maximum of desriminant value
3)number of tests

In directory matrix_data are generated tests and answers
