
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

#define easyshell_RL_BUFSIZE 1024

extern int easyshell_num_builtins(void);
extern char *builtin_str[];
extern int (*builtin_func[]) (char **);

char *prompt = "easyshell> ";

char *easyshell_read_line(void)
{
	char* input = readline(prompt);
	add_history(input);

	return input;
}

#define EASYSHELL_TOK_BUFSIZE 64
#define EASYSHELL_TOK_DELIM " \t\r\n\a"

char **easyshell_split_line(char *line)
{
	int bufsize = EASYSHELL_TOK_BUFSIZE;
	int position = 0;
	char **tokens = malloc(sizeof(char*) * bufsize);
	char *token;

	if(!tokens){
		fprintf(stderr, "easyshell: tokens allocation error");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, EASYSHELL_TOK_DELIM);

	while(token != NULL) {
		tokens[position] = token;
		position++;

		if(position >= bufsize) {
			bufsize += EASYSHELL_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
				fprintf(stderr, "easyshell: tokens reallocation failure\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, EASYSHELL_TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}

int easyshell_launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();

	if (pid == 0) {
		if (execvp(args[0], args) == -1) {
			perror("easyshell");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		perror("easyshell");
	} else {
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int easyshell_execute(char **args)
{
	int i;

	if (args[0] == NULL) {
		// Empty command was entered.
		return 1;
	}

	for(i = 0; i < easyshell_num_builtins(); i++) {
		if (strcmp(args[0], builtin_str[i]) == 0) {
			return (*builtin_func[i])(args);
		}
	}

	return easyshell_launch(args);
}

void easyshell_loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		line = easyshell_read_line();
		args = easyshell_split_line(line);
		status = easyshell_execute(args);

		free(line);
		free(args);

	}while(status);
}
