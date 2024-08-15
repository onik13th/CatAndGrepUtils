#include "file_handler.h"

void grep_file(FILE *file, GrepFlags flags, char const *filename, regex_t *preg,
               int count_file) {
  char *line = NULL;
  size_t length = 0;
  regmatch_t match;
  int line_count = 0;

  while (getline(&line, &length, file) > 0) {
    line_count++;

    if (flags.listMatchingFiles) {
      rewind(file);  // перематывание файла в начало
      print_matching_files(file, filename, preg);
      break;  // Прерываем дальнейшую обработку, если активен флаг -l
    }

    bool matched = !regexec(preg, line, 1, &match, 0);
    if (flags.invertMatch) matched = !matched;  // для инвертирующего флага -v

    if (matched) {
      if (flags.printMatched) {
        print_matched_part(line, filename, preg, match, count_file, line_count,
                           flags);
      } else {
        if (count_file > 1 && !flags.suppressFileNames) {
          printf("%s:", filename);  // Печать имени файла для каждой строки
        }
        if (flags.numberOfLine) {
          printf("%d:", line_count);
        }
        printf("%s", line);
      }
    }
  }
  free(line);
}