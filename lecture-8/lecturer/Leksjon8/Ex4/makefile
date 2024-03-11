#
# Generic makefile for compiling and linking more than one source file
#
TARGET = test
OBJS = $(TARGET).o list.o # List object files here
DEPS = list.h makefile
# CFLAGS = -O2
CFLAGS = -O0 -g

%.o: %.c $(DEPS)
	gcc -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

.phony: clean
clean:
	rm -f *.o $(TARGET)

