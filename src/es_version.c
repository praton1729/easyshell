
#include <es_log.h>

#define version 0.1

int es_version(char **args)
{
	es_print("Version info: %.1f\n", version);
	return 1;
}

