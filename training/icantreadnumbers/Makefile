CC = gcc
CFLAGS = -Wall -O2 -pedantic
TARGET = build/numtotxt

all: src/main.c
	@mkdir -p build/
	$(CC) $(CFLAGS) src/main.c -o $(TARGET)

clean:
	@rm -rf build/

.phony:all all clean
