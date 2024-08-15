#ifndef GREP_MAIN_CONTROLLER_H
#define GREP_MAIN_CONTROLLER_H
#define _GNU_SOURCE

#include "../../common/flag_struct.h"
#include "../flags/grep_flags.h"
#include "../handler/file_handler.h"
#include "../parser/flag_parser.h"

void grep(int argc, char *argv[], GrepFlags flags);
char *build_combined_pattern(GrepFlags flags);

#endif