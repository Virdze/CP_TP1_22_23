CC = gcc
BIN = bin/
SRC = src/
HEADERS = headers/
EXEC = k_means

CFLAGS = -O2 

.DEFAULT_GOAL = k_means

k_means: $(SRC)k_means.c $(BIN)utils.o 
	$(CC) $(CFLAGS) $(SRC)k_means.c $(BIN)utils.o -o $(BIN)$(EXEC)

$(BIN)utils.o: $(SRC)utils.c $(HEADERS)utils.h
	$(CC) $(CFLAGS) -c $(SRC)utils.c -o $(BIN)utils.o

clean:
	rm -r bin/*

run:
	./$(BIN)$(EXEC)