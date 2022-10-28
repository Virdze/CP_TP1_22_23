CC = gcc
BIN = bin/
SRC = src/
INCLUDES = include/
EXEC = k_meansv2

CFLAGS = -lm -Wall -O2 -g 

.DEFAULT_GOAL = k_meansv2

k_meansv2: $(BIN)utilsv2.o $(BIN)k_meansv2.o 
	$(CC) $(BIN)k_meansv2.o $(BIN)utilsv2.o -o $(BIN)$(EXEC) $(CFLAGS)

$(BIN)utilsv2.o: $(SRC)utilsv2.c 
	$(CC) -c $(SRC)utilsv2.c -o $(BIN)utilsv2.o $(CFLAGS)

$(BIN)k_meansv2.o: $(SRC)k_meansv2.c $(INCLUDES)utilsv2.h
	$(CC) -c $(SRC)k_meansv2.c -o $(BIN)k_meansv2.o $(CFLAGS)

clean:
	rm -r bin/*

run:
	./$(BIN)$(EXEC)