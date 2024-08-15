#ifndef GREP_FLAGS_H
#define GREP_FLAGS_H
#define _GNU_SOURCE

#include "../../common/flag_struct.h"

void grep_counter(FILE *file, GrepFlags flags, char const *filename,
                  regex_t *preg, int count_file);  // -c
void print_matching_files(FILE *file, const char *filename,
                          regex_t *preg);  // -l
void print_matched_part(char *line, const char *filename, regex_t *preg,
                        regmatch_t match, int count_file, int line_number,
                        GrepFlags flags);  // -o
void init_flags(GrepFlags *flags);
void free_flags(GrepFlags *flags);
void add_pattern(GrepFlags *flags, const char *pattern);
void load_patterns_from_file(GrepFlags *flags, const char *filename);

#endif