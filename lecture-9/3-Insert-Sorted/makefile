INCLDIR = ./include
TARGET = ex2
CC = gcc
CFLAGS = -O0
CFLAGS += -I$(INCLDIR)

OBJDIR = ./obj

_DEPS = ex2.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = ex2.o main.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~



