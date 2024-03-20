INCLDIR = ./include
TARGET = keyvalue
CC = gcc
CFLAGS = -O0
CFLAGS += -I$(INCLDIR)

OBJDIR = ./obj

_DEPS = keyvalue.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = main.o keyvalue.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~



