#ifndef GREP_FILE_HANDLER_H
#define GREP_FILE_HANDLER_H
#define _GNU_SOURCE

#include "../../common/flag_struct.h"
#include "../flags/grep_flags.h"

void grep_file(FILE *file, GrepFlags flags, char const *filename, regex_t *preg,
               int count_file);

#endif