CC = gcc
CFLAGS = -Wall -O2 -pedantic
TARGET = wordle
SRCDIR = src

all: $(TARGET)

$(TARGET): $(SRCDIR)/main.c
	$(CC) $(CFLAGS) $(SRCDIR)/main.c -o $(TARGET) 

clean: 
	rm $(TARGET)