CC = gcc
CFLAGS = -Wall -O2 -I.
SRC = src_c/main.c src_c/embed.c src_c/rag_store.c src_c/model.c src_c/ingest.c
OBJ = $(SRC:.c=.o)
TARGET = jajacoder_core

all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ) $(TARGET)
