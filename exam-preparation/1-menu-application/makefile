INCLDIR = ./include
TARGET = movieapplication
CC = gcc
CFLAGS = -O0
CFLAGS += -I$(INCLDIR)

OBJDIR = ./obj

_DEPS = actor.h input.h menu.h movie.h utils.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = utils.o movie.o movieapplication.o menu.o input.o actor.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) ../../my-static-library/libsdlogger.a

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~



