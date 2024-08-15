#ifndef CAT_MAIN_CONTROLLER_H
#define CAT_MAIN_CONTROLLER_H

#include "../../common/flag_struct.h"
#include "../handler/file_handler.h"

void cat(int argc, char *argv[], CatFlags flags, const char *table[static 256]);

#endif