/*
 * =====================================================================================
 *
 *       Filename:  psh_builtins.c
 *
 *    Description:  Basic shell utilities
 *
 *        Version:  1.0
 *        Created:  Monday 19 April 2021 02:19:52  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  PRATHU BARONIA (praton), prathu.baronia@oneplus.com
 *   Organization:  OnePlus RnD
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int psh_cd(char **args);
int psh_help(char **args);
int psh_exit(char **args);

char *builtin_str[] = {
	"cd",
	"help",
	"exit"
};

int (*builtin_func[]) (char **) = {
	&psh_cd,
	&psh_help,
	&psh_exit
};

int psh_num_builtins()
{
	return sizeof(builtin_str) / sizeof(char*);
}

int psh_cd(char **args)
{
	if (args[1] == NULL) {
		fprintf(stderr, "psh: expected argument to cd\n");
	} else {
		if (chdir(args[1]) != 0) {
			perror("psh");
		}
	}
	return 1;
}

int psh_help(char **args)
{
	int i;
	printf("Prathu Baronia's PSH\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are the builtins:\n");

	for(i = 0; i < psh_num_builtins(); i++) {
		printf(" %s\n", builtin_str[i]);
	}

	printf("Use the man command for information on other programs. \n");
	return 1;
}

int psh_exit(char **args)
{
	exit(EXIT_SUCCESS);
	return 0;
}
