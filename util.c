/*
 * =====================================================================================
 *
 *       Filename:  util.c
 *
 *    Description:  praton shell helper routines
 *
 *        Version:  1.0
 *        Created:  Monday 19 April 2021 01:38:29  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  PRATHU BARONIA (praton), prathu.baronia@oneplus.com
 *   Organization:  OnePlus RnD
 *
 * =====================================================================================
 */

#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PSH_RL_BUFSIZE 1024

extern int psh_num_builtins(void);
extern char *builtin_str[];
extern int (*builtin_func[]) (char **);

char *psh_read_line(void)
{
	int bufsize = PSH_RL_BUFSIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * bufsize);
	int c;
	
	if(!buffer) {
		fprintf(stderr, "psh: buffer allocation failure\n");
		exit(EXIT_FAILURE);
	}

	while(1) {
		c = getchar();

		if (c == EOF || c == '\n') {
			buffer[position] = '\0';
			return buffer;
		} else {
			buffer[position] = c;
		}
		position++;

		if (position >= bufsize) {
			bufsize += PSH_RL_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if (!buffer) {
				fprintf(stderr, "psh: buffer reallocation failure\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

#define PSH_TOK_BUFSIZE 64
#define PSH_TOK_DELIM " \t\r\n\a"

char **psh_split_line(char *line)
{
	int bufsize = PSH_TOK_BUFSIZE;
	int position = 0;
	char **tokens = malloc(sizeof(char*) * bufsize);
	char *token;

	if(!tokens){
		fprintf(stderr, "psh: tokens allocation error");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, PSH_TOK_DELIM);

	while(token != NULL) {
		tokens[position] = token;
		position++;

		if(position >= bufsize) {
			bufsize += PSH_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
				fprintf(stderr, "psh: tokens reallocation failure\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, PSH_TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}

int psh_launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();

	if (pid == 0) {
		if (execvp(args[0], args) == -1) {
			perror("psh");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		perror("psh");
	} else {
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int psh_execute(char **args)
{
	int i;

	if (args[0] == NULL) {
		// Empty command was entered.
		return 1;
	}

	for(i = 0; i < psh_num_builtins(); i++) {
		if (strcmp(args[0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(args);
		}
	}

	printf("Launching %s\n", args[0]);
	return psh_launch(args);
}

void psh_loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf("psh> ");
		line = psh_read_line();
		args = psh_split_line(line);
		status = psh_execute(args);

		free(line);
		free(args);

	}while(status);
}
