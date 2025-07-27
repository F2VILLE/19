CC = gcc
CFLAGS = -Wall -O2 -pedantic
TARGET = lolnet
SRCDIR = src
OUTDIR = build

all: $(SRCDIR)/main.c 
	@mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) $(SRCDIR)/main.c -o $(OUTDIR)/$(TARGET)

clean:
	rm -rf $(OUTDIR)
	rm $(TARGET)
