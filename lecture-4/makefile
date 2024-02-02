# makefile template

INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)

OBJDIR = obj

_DEPS =
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = exercise-3-scanf.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)


exercise-3-scanf: $(OBJS)
		gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
		rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*