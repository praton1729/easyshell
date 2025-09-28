
EXEC := easyshell.elf

SOURCES := src/main.c src/util.c src/builtins.c

LIBS := readline

all: $(EXEC)

$(EXEC): $(SOURCES)
	gcc -I./include/ $^ -l$(LIBS) -o $@

clean:
	rm $(EXEC)
