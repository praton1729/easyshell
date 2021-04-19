EXEC= psh
SOURCES= main.c util.c psh_builtins.c
LIBS= readline

all: $(EXEC)

$(EXEC): $(SOURCES)
	gcc  $^ -l$(LIBS) -o $@

clean:
	rm $(EXEC)
