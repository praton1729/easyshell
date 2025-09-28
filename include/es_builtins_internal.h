
#pragma once

struct es_cmd {
	char *cmd_name;
	int (*cmd_handler)(char **arg);
};

#define DECLARE_CMD(name, handler) \
	{                          \
	.cmd_name = name,          \
	.cmd_handler = handler     \
	}

#define DECLARE_END DECLARE_CMD(NULL, NULL)

