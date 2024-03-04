INCLDIR = ./include
TARGET = exercise-3-extend-buffer-for-long
CC = gcc
CFLAGS = -O0
CFLAGS += -I$(INCLDIR)

OBJDIR = ./obj

_DEPS = exercise-3-extend-buffer.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = exercise-3-extend-buffer.o main.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~



