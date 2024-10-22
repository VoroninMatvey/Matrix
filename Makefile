TARGET = determination
CC = g++
IFLAGS = ./include/
PREF_OBJ = ./obj/
PREF_SRC = ./src/

$(TARGET) : $(PREF_OBJ) $(PREF_OBJ)Matrix.o
	$(CC) -I $(IFLAGS) $(PREF_OBJ)Matrix.o -o $(TARGET)

$(PREF_OBJ) :
	mkdir $(PREF_OBJ)

$(PREF_OBJ)Matrix.o : $(PREF_SRC)Matrix.cpp
	$(CC) -I $(IFLAGS) -c $(PREF_SRC)Matrix.cpp -o $(PREF_OBJ)Matrix.o

clean:
	rm $(TARGET)
	rm $(PREF_OBJ)*.o
