#function declarations + build system
#     
# Build script for compiling the Regex-Lite project.
# Generates the 'regex-lite' executable from:
# main.c, regex.c, search.c, regex.h

CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = regex-lite
OBJS = main.o regex.o search.o
.PHONY: all clean run

all: $(TARGET)

# Link Final Executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
./$(TARGET) $(FILE) $(PATTERN)

clean:
	rm -f $(OBJS) $(TARGET)
