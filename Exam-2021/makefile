INCLDIR = ./include
TARGET = exam2021threads
CC = gcc
CFLAGS = -O0
CFLAGS += -I$(INCLDIR)
LINKEXTRA = -lpthread

OBJDIR = ./obj

_DEPS =exam2021threads.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = exam2021threads.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LINKEXTRA)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
