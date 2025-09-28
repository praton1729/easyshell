
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <es_builtins.h>

#define ES_TOK_BUFSIZE 64
#define ES_TOK_DELIM " \t\r\n\a"

char *prompt = "easyshell> ";

char *es_read_line(void)
{
	char* input = readline(prompt);
	add_history(input);

	return input;
}

char **es_split_line(char *line)
{
	int bufsize = ES_TOK_BUFSIZE;
	int position = 0;
	char **tokens = malloc(sizeof(char*) * bufsize);
	char *token;

	if(!tokens){
		fprintf(stderr, "easyshell: tokens allocation error");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, ES_TOK_DELIM);

	while(token != NULL) {
		tokens[position] = token;
		position++;

		if(position >= bufsize) {
			bufsize += ES_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
				fprintf(stderr, "easyshell: tokens reallocation failure\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, ES_TOK_DELIM);
	}

	tokens[position] = NULL;
	return tokens;
}
