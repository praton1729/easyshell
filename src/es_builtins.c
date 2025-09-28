
#include <string.h>
#include <es_log.h>
#include <es_help.h>
#include <es_version.h>
#include <es_exit.h>
#include <es_builtins_internal.h>

struct es_cmd cmd_list[] = {
	DECLARE_CMD("help", &es_help),
	DECLARE_CMD("version", &es_version),
	DECLARE_CMD("exit", &es_exit),
	DECLARE_END
};

void es_print_builtins()
{
	struct es_cmd *cmd = cmd_list;

	while(cmd->cmd_name) {
		es_print("\t%s\n", cmd->cmd_name);
		cmd++;
	}
}

int es_execute(char **args)
{
	struct es_cmd *cmd = cmd_list;

	if (args[0] == NULL) {
		// Empty command was entered.
		return -1;
	}

	while(cmd->cmd_name) {
		if (strcmp(args[0], cmd->cmd_name) == 0)
			return cmd->cmd_handler(args);
		cmd++;
	}

	return -1;
}
