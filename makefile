CC = clang
CFLAGS = -Wall -Wextra -std=c11
TARGET = squeeze

all: $(TARGET)

$(TARGET): main.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm $(TARGET) *.o