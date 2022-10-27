CC = gcc
BIN = bin/
SRC = src/
INCLUDES = include/
EXEC = k_means

CFLAGS = -lm -Wall -O2

.DEFAULT_GOAL = k_means

k_means: $(BIN)utils.o $(BIN)k_means.o 
	$(CC) $(BIN)k_means.o $(BIN)utils.o -o $(BIN)$(EXEC) $(CFLAGS)

$(BIN)utils.o: $(SRC)utils.c 
	$(CC) -c $(SRC)utils.c -o $(BIN)utils.o $(CFLAGS)

$(BIN)k_means.o: $(SRC)k_means.c $(INCLUDES)utils.h
	$(CC) -c $(SRC)k_means.c -o $(BIN)k_means.o $(CFLAGS)

clean:
	rm -r bin/*

run:
	./$(BIN)$(EXEC)