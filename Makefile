CC = clang

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

TARGET = main
CLI = cli

all: bin $(TARGET)

bin:
	mkdir -p bin

$(TARGET): src/$(TARGET).c bin
	$(CC) $(CFLAGS) -o bin/$(TARGET) src/$(TARGET).c $(LFLAGS)

clean:
	rm -f bin/$(TARGET)
	rmdir bin

run: $(TARGET)
	./bin/$(TARGET)

cli: src/$(CLI).c bin
	$(CC) $(CFLAGS) -o bin/$(CLI) src/$(CLI).c $(LFLAGS)

.PHONY: all clean
