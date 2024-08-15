#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "../../common/flag_struct.h"
#include "../flags/cat_flags.h"
#include <stdbool.h>
#include <stdio.h>

void cat_file(FILE *file, CatFlags flags, const char *table[static 256]);

#endif