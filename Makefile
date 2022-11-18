CC = gcc
BIN = bin/
SRC = src/
INCLUDES = include/
EXEC = k_meansv2
EXEC_PAR = k_meansv2_par
THREADS = 16
CP_CLUSTERS = 4

CFLAGS = -lm -Wall -O2 -g
CFLAGS_PAR = -O2 -fopenmp -lm

.DEFAULT_GOAL = k_meansv2_par

k_meansv2: $(BIN)utilsv2.o $(BIN)k_meansv2.o 
	$(CC) $(BIN)k_meansv2.o $(BIN)utilsv2.o -o $(BIN)$(EXEC) $(CFLAGS)

k_meansv2_par: $(BIN)utilsv2.o $(BIN)k_meansv2_par.o
	$(CC) $(BIN)k_meansv2_par.o $(BIN)utilsv2.o -o $(BIN)$(EXEC_PAR) $(CFLAGS_PAR) 

$(BIN)utilsv2.o: $(SRC)utilsv2.c 
	$(CC) -c $(SRC)utilsv2.c -o $(BIN)utilsv2.o $(CFLAGS)

$(BIN)k_meansv2.o: $(SRC)k_meansv2.c $(INCLUDES)utilsv2.h
	$(CC) -c $(SRC)k_meansv2.c -o $(BIN)k_meansv2.o $(CFLAGS)

$(BIN)k_meansv2_par.o: $(SRC)k_meansv2_par.c $(INCLUDES)utilsv2.h
	$(CC) -c $(SRC)k_meansv2_par.c -o $(BIN)k_meansv2_par.o $(CFLAGS_PAR)

clean:
	rm -r bin/*

runseq:
	./$(BIN)$(EXEC) 10000000 $(CP_CLUSTERS) 

runpar:
	./$(BIN)$(EXEC_PAR) 10000000 $(CP_CLUSTERS) $(THREADS)