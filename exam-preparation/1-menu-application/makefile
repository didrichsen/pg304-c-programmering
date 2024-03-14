INCLDIR = ./include
TARGET = menuapplication
CC = gcc
CFLAGS = -O0
CFLAGS += -I$(INCLDIR)

OBJDIR = ./obj

_DEPS = sdlogger.h menuapplication.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = menu.o menuapplication.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) ../../my-static-library/libsdlogger.a

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~



