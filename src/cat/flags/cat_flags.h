#ifndef CAT_FLAGS_H
#define CAT_FLAGS_H

#include <string.h>

void cat_set_table(const char *table[static 256]);
void cat_set_endl(const char *table[static 256]);
void cat_set_tab(const char *table[static 256]);
void cat_set_non_printble(const char *table[static 256]);

#endif