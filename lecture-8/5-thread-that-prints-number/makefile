INCLDIR = ./include
TARGET = exercise-5-threads
CC = gcc
CFLAGS = -O0
CFLAGS += -I$(INCLDIR)

OBJDIR = ./obj

LIBDIR = ../../my-static-library
LDFLAGS = -L$(LIBDIR) -lsdlogger

_DEPS = sdlogger.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = threads.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
