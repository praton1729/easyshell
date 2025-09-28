
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <es_log.h>

#define version 0.1

int es_help(char **args);
int es_exit(char **args);
int es_version(char **args);

char *builtin_str[] = {
	"help",
	"version",
	"exit"
};

int (*builtin_func[]) (char **) = {
	&es_help,
	&es_version,
	&es_exit
};

int es_num_builtins()
{
	return sizeof(builtin_str) / sizeof(char*);
}

int es_version(char **args)
{
	es_print("Version info: %.1f\n", version);
	return 1;
}

int es_help(char **args)
{
	es_print("Easyshell, a simple bootstrappable shell\n");
	es_print("The following commands are builtin:\n");

	for(int i = 0; i < es_num_builtins(); i++) {
		es_print("\t%s\n", builtin_str[i]);
	}

	return 1;
}

int es_exit(char **args)
{
	exit(EXIT_SUCCESS);
	return 0;
}

int es_execute(char **args)
{
	int i;

	if (args[0] == NULL) {
		// Empty command was entered.
		return -1;
	}

	for(i = 0; i < es_num_builtins(); i++) {
		if (strcmp(args[0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(args);
		}
	}

	return -1;
}

