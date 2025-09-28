
#pragma once

int easyshell_num_builtins(void);
int easyshell_execute(char **args);

extern char *builtin_str[];
extern int (*builtin_func[]) (char **);
