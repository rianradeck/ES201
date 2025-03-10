CC = /usr/ensta/pack/simplescalar-3v0d/bin/sslittle-na-sstrix-gcc
CFLAGS = -O3

SRCS = sha_driver.c sha.c
OBJS = sha_driver.o sha.o
TARGET = sha_driver.ss

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
