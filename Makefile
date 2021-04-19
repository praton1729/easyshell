EXEC= psh
SOURCES= main.c util.c psh_builtins.c

all: $(EXEC)

$(EXEC): $(SOURCES)
	gcc -o $@ $^

clean:
	rm $(EXEC)
