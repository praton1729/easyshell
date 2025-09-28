
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define version 0.1

int easyshell_help(char **args);
int easyshell_exit(char **args);
int easyshell_version(char **args);

char *builtin_str[] = {
	"help",
	"version",
	"exit"
};

int (*builtin_func[]) (char **) = {
	&easyshell_help,
	&easyshell_version,
	&easyshell_exit
};

int easyshell_num_builtins()
{
	return sizeof(builtin_str) / sizeof(char*);
}

int easyshell_version(char **args)
{
	printf("Version info: %.1f\n", version);
	return 1;
}

int easyshell_help(char **args)
{
	int i;
	printf("Welcome to easyshell!!\n\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are the builtins:\n\n");

	for(i = 0; i < easyshell_num_builtins(); i++) {
		printf(" %s\n", builtin_str[i]);
	}

	printf("\nUse the man command for information on other programs. \n");
	return 1;
}

int easyshell_exit(char **args)
{
	exit(EXIT_SUCCESS);
	return 0;
}
