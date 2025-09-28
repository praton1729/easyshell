
#pragma once

#include <stdio.h>

#define ERROR_LABEL "\033[31mERROR:\033[0m "  // Red colored "ERROR:" label
#define INFO_LABEL "\033[32mINFO:\033[0m "    // Green colored "INFO:" label

#define es_error(fmt, ...) fprintf(stderr, ERROR_LABEL fmt, ##__VA_ARGS__)
#define es_info(fmt, ...)  fprintf(stdout, INFO_LABEL fmt, ##__VA_ARGS__)
#define es_print(fmt, ...) fprintf(stdout, fmt, ##__VA_ARGS__)
