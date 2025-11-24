#function declarations + build system
#     
# Build script for compiling the Regex-Lite project.
# Generates the 'regex-lite' executable from:
# main.c, regex.c, search.c, regex.h

CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = regex-lite
OBJS = main.o regex.o search.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)
