#ifndef FLAG_PARSER_H
#define FLAG_PARSER_H

#include "../../common/flag_struct.h"
#include "../flags/grep_flags.h"

GrepFlags grep_parse_flags(int argc, char *argv[]);

#endif