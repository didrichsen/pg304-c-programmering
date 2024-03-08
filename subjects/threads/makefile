INCLDIR = ./include
TARGET = mutex
CC = gcc
CFLAGS = -O0
CFLAGS += -I$(INCLDIR)
LINKEXTRA = -lpthread

OBJDIR = ./obj

_DEPS =
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = mutex.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LINKEXTRA)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~
