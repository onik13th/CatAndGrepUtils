#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdbool.h>
#include <stdio.h>

#include "../../common/flag_struct.h"
#include "../flags/cat_flags.h"

void cat_file(FILE *file, CatFlags flags, const char *table[static 256]);

#endif