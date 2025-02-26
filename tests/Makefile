TARGET = generator
CC = g++
CXXFLAGS = -std=c++23
PREF_OBJ = ./obj/
PREF_SRC = ./src/
IFLAGS = ./include/


$(TARGET) : $(PREF_OBJ) $(PREF_OBJ)generator.o
	$(CC) $(CXXFLAGS) $(PREF_OBJ)generator.o -o $(TARGET)

$(PREF_OBJ) : 
	mkdir -p $(PREF_OBJ)

$(PREF_OBJ)generator.o : $(PREF_SRC)generator.cpp
	$(CC) -I $(IFLAGS) -c $(PREF_SRC)generator.cpp -o $(PREF_OBJ)generator.o

clean : 
	rm $(TARGET) 
	rm $(PREF_OBJ)*.o