
#pragma once

int es_num_builtins(void);
int es_execute(char **args);

extern char *builtin_str[];
extern int (*builtin_func[]) (char **);
