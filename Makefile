# Compilador e instruções
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -O2

# Diretórios
SRC_DIR = src
BIN_DIR = bin

# Executavel
TARGET = $(BIN_DIR)/eventos

# Arquivos fonte e objeto
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

# Target padrão
.PHONY: all clean

all: $(BIN_DIR) $(TARGET)

# Criar o diretório bin se não existir
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Conectar objetos ao executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilar arquivos C para objetos
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos de compilação
clean:
	rm -rf $(BIN_DIR) $(SRC_DIR)/*.o