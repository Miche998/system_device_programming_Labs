# Compilatore
CC = gcc

# Flag di compilazione
CFLAGS = -Wall -Wextra -g -pthread

# Directory
BIN_DIR = bin

# Targets principali
TARGETS = $(BIN_DIR)/ex02 $(BIN_DIR)/ex03 $(BIN_DIR)/ex03_rec \
         $(BIN_DIR)/ex04 $(BIN_DIR)/ex05

# Target principale
all: makedirs $(TARGETS)

# Crea directory bin se non esiste
makedirs:
	@mkdir -p $(BIN_DIR)

$(BIN_DIR)/ex02: ex02.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/ex03: ex03.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/ex03_rec: ex03_rec.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/ex04: ex04.c
	$(CC) $(CFLAGS) $< -o $@ -pthread

$(BIN_DIR)/ex05: ex05.c
	$(CC) $(CFLAGS) $< -o $@ -pthread

# Target per i file di test
test_files: file_1.txt file_2.txt file_3.txt

file_1.txt:
	@echo "1 100000 Romano Antonio 25" > file_1.txt
	@echo "2 150000 Fabrizi Aldo 22" >> file_1.txt
	@echo "3 200000 Verdi Giacomo 15" >> file_1.txt
	@echo "4 250000 Rossi Luigi 30" >> file_1.txt

# Pulisci i file compilati e generati
clean:
	rm -rf $(BIN_DIR)
	rm -f file_2.txt file_3.txt

# Pulisci tutto, inclusi i file di input
cleanall: clean
	rm -f file_1.txt

# Non considerare i file con lo stesso nome dei target
.PHONY: all clean cleanall makedirs test_files

# Regole di utilizzo:
help:
	@echo "Makefile per Lab02 - Utilizzo:"
	@echo "  make        : compila tutti gli esercizi"
	@echo "  make clean  : rimuove i file compilati"
	@echo "  make cleanall: rimuove tutti i file generati e compilati"
	@echo "  make test_files: crea i file di test necessari"