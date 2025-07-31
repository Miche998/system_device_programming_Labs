# Compilatore
CC = gcc

# Flag di compilazione
CFLAGS = -Wall -Wextra -g -pthread

# Directory
BIN_DIR = bin

# Tutti gli eseguibili
TARGETS = $(BIN_DIR)/ex01 $(BIN_DIR)/ex02 $(BIN_DIR)/ex03 $(BIN_DIR)/ex04 \
         $(BIN_DIR)/ex05concurrent $(BIN_DIR)/e05recursive $(BIN_DIR)/ex06 \
         $(BIN_DIR)/ex07 $(BIN_DIR)/ex08

# Target principale
all: makedirs $(TARGETS)

# Crea la directory bin se non esiste
makedirs:
	@mkdir -p $(BIN_DIR)

# Regole di compilazione per ogni esercizio
$(BIN_DIR)/ex01: ex01.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/ex02: ex02.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/ex03: ex03.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/ex04: ex04.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/ex05concurrent: ex05concurrent.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/e05recursive: e05recursive.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/ex06: ex06.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/ex07: ex07.c
	$(CC) $(CFLAGS) $< -o $@ -pthread

$(BIN_DIR)/ex08: ex08.c
	$(CC) $(CFLAGS) $< -o $@ -pthread

# Pulisci i file compilati
clean:
	rm -rf $(BIN_DIR)

# Non considerare i file con lo stesso nome dei target
.PHONY: all clean makedirs