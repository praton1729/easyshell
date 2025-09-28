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

#define version 0.1

int psh_help(char **args);
int psh_exit(char **args);
int psh_version(char **args);

char *builtin_str[] = {
	"help",
	"version",
	"exit"
};

int (*builtin_func[]) (char **) = {
	&psh_help,
	&psh_version,
	&psh_exit
};

int psh_num_builtins()
{
	return sizeof(builtin_str) / sizeof(char*);
}

int psh_version(char **args)
{
	printf("Version info: %.1f\n", version);
	return 1;
}

int psh_help(char **args)
{
	int i;
	printf("Welcome to psh!!\n\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are the builtins:\n\n");

	for(i = 0; i < psh_num_builtins(); i++) {
		printf(" %s\n", builtin_str[i]);
	}

	printf("\nUse the man command for information on other programs. \n");
	return 1;
}

int psh_exit(char **args)
{
	exit(EXIT_SUCCESS);
	return 0;
}
