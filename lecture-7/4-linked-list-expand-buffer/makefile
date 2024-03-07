INCLDIR = ./include
TARGET = exercise-linked-list
CC = gcc
CFLAGS = -O0
CFLAGS += -I$(INCLDIR)

OBJDIR = ./obj

LIBDIR = ../../library
LDFLAGS = -L$(LIBDIR) -lsdlogger

_DEPS = linked-list.h sdlogger.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = linked-list.o main.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
