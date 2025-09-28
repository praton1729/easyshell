
#include <es_builtins.h>
#include <es_log.h>

int es_help(char **args)
{
	es_print("Easyshell, a simple bootstrappable shell\n");
	es_print("The following commands are builtin:\n");
	es_print_builtins();
	return 1;
}
