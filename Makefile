CC = gcc
BIN = bin/
SRC = src/
INCLUDES = include/
EXEC = k_means

CFLAGS = -O2 

.DEFAULT_GOAL = k_means

k_means: $(SRC)k_means.c 
	$(CC) $(CFLAGS) $(SRC)k_means.c -o $(BIN)$(EXEC)

$(SRC)k_means.c:  

clean:
	rm -r bin/*

run:
	./$(BIN)$(EXEC)