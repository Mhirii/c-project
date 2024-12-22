CC = clang

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall

TARGET = main

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

.PHONY: all clean
