
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <es_line.h>
#include <es_builtins.h>

void easyshell_loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		line = easyshell_read_line();
		args = easyshell_split_line(line);
		status = easyshell_execute(args);

		if (status < 0) {
			if (strcmp(line, "") == 0) goto free_line;
			fprintf(stderr, "cmd not found, try help\n");
		}

free_line:
		free(line);
		free(args);

	} while(status);
}

int main(int argc, char **argv)
{
	easyshell_loop();
	return EXIT_SUCCESS;
}
