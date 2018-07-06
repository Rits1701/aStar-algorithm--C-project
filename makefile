CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c99 -c
SOURCES = $(wildcard *c)
OBJECTS = $(SOURCES:.c=.o)
LDFLAGS = -lm
EXECUTABLE = map

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
