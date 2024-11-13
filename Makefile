CC = gcc
CFLAGS = -Isrc/headers -Wall
LDFLAGS =

# Source files
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)

# Executable name
EXECUTABLE=game_server

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f src/*.o $(EXECUTABLE)

.PHONY: all clean
