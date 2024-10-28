TARGET = determination
CC = g++
CXXFLAGS = -std=c++23
IFLAGS = ./include/
PREF_OBJ = ./obj/
PREF_SRC = ./src/

$(TARGET) : $(PREF_OBJ) $(PREF_OBJ)Matrix.o
	$(CC) $(CXXFLAGS) $(PREF_OBJ)Matrix.o -o $(TARGET)

$(PREF_OBJ) :
	mkdir -p $(PREF_OBJ)

$(PREF_OBJ)Matrix.o : $(PREF_SRC)Matrix.cpp
	$(CC) $(CXXFLAGS) -I $(IFLAGS) -c $(PREF_SRC)Matrix.cpp -o $(PREF_OBJ)Matrix.o

clean:
	rm $(PREF_OBJ)*.o
	rm $(TARGET)