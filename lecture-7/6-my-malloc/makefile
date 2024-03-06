INCLDIR = ./include
TARGET = my-alloc
CC = gcc
CFLAGS = -O0
CPPFLAGS = -I$(INCLDIR)
LIBDIR = ../../my-static-library
LDFLAGS = -L$(LIBDIR)
LIBS = -lsdlogger

OBJDIR = ./obj

_DEPS = myalloc.h sdlogger.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = myalloc.o main.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o $(INCLDIR)/*~
