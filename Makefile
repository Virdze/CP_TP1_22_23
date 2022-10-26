CC = gcc
BIN = bin/
SRC = src/
HEADERS = headers/
EXEC = k_means

CFLAGS = -lm -O2

.DEFAULT_GOAL = k_means

<<<<<<< HEAD
k_means: $(BIN)utils.o $(BIN)k_means.o 
	$(CC) $(BIN)k_means.o $(BIN)utils.o -o $(BIN)$(EXEC) $(CFLAGS)

$(BIN)utils.o: $(SRC)utils.c 
	$(CC) -c $(SRC)utils.c -o $(BIN)utils.o $(CFLAGS)

$(BIN)k_means.o: $(SRC)k_means.c $(INCLUDES)utils.h
	$(CC) -c $(SRC)k_means.c -o $(BIN)k_means.o $(CFLAGS)
=======
k_means: $(SRC)k_means.c $(BIN)utils.o 
	$(CC) $(CFLAGS) $(SRC)k_means.c $(BIN)utils.o -o $(BIN)$(EXEC)

$(BIN)utils.o: $(SRC)utils.c $(HEADERS)utils.h
	$(CC) $(CFLAGS) -c $(SRC)utils.c -o $(BIN)utils.o
>>>>>>> 630de53185b3c463a46b729ede0dc1b9753ecef7

clean:
	rm -r bin/*

run:
	./$(BIN)$(EXEC)