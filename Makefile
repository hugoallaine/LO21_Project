TARGET=project
CFLAGS=-Wall
LDFLAGS=
CC=gcc

all: $(TARGET)

$(TARGET): main.c individu.o population.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) *.o
