CC ?= gcc
CFLAGS ?= -Wall -Wextra -Werror -g

LDLIBS ?= -lm -ltps -lSDL2 -lSDL2_ttf

INCLUDE_PATH = ./include
TARGET   = arbres
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)

doc:
	doxygen Doxyfile

.PHONY: clean cov
clean:
	rm -r $(OBJDIR)/*.o
	rm -r $(OBJDIR)/*.gcda
	rm -r $(OBJDIR)/*.gcno
	rm -r $(BINDIR)/$(TARGET)