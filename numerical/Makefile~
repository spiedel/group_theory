# This makefile will combile our solution
CC = g++
EXE = Prog

FLAGS= (-std=c++11)
OBJ= script.o grid_input.o

$(EXE): $(OBJ)
	$(CC) -std=c++11 -o $@ $^

%.o:%.cpp
	$(CC) -std=c++11 -c $<

.PHONY: clean test
clean:
	rm *.o
	rm $(EXE)
