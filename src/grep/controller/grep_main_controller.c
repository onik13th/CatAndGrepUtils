#include "grep_main_controller.h"

void grep(int argc, char *argv[], GrepFlags flags) {
  int count_files = argc - optind;
  if (count_files == 0) {
    fprintf(stderr, "No file provided\n");
    exit(EXIT_FAILURE);
  }

  char *combined_pattern =
      build_combined_pattern(flags);  // объединение регулярки в одно большое

  regex_t preg;
  if (regcomp(
          &preg, combined_pattern,
          flags.regex_flag)) {  // компиляция полученного регулярного выражения
    fprintf(stderr, "Failed to compile regex\n");
    free(combined_pattern);
    exit(EXIT_FAILURE);
  }
  free(combined_pattern);  // освобождение строки шаблона сразу после компиляции

  for (int i = optind; i < argc; i++) {  // обработка каждого файла
    FILE *file = fopen(argv[i], "rb");
    if (!file) {
      if (!flags.suppressErrorMessage) {
        fprintf(stderr, "s21_grep: %s: No such file or directory\n", argv[i]);
      }
      continue;
    }

    if (!flags.counter) {
      grep_file(file, flags, argv[i], &preg, count_files);
    } else {
      grep_counter(file, flags, argv[i], &preg, count_files);
    }

    fclose(file);
  }
  regfree(&preg);
  free_flags(&flags);
}

char *build_combined_pattern(GrepFlags flags) {
  if (flags.num_patterns == 1) {
    return strdup(flags.patterns[0]);
  }

  int total_length = 0;
  for (int i = 0; i < flags.num_patterns; i++) {
    total_length += strlen(flags.patterns[i]) + 1;  // +1 для '|'
  }

  char *combined_pattern = malloc(total_length);
  if (!combined_pattern) {
    fprintf(stderr, "Memory allocation error\n");
    exit(EXIT_FAILURE);
  }

  strcpy(combined_pattern, flags.patterns[0]);
  for (int i = 1; i < flags.num_patterns; i++) {
    strcat(combined_pattern, "|");
    strcat(combined_pattern, flags.patterns[i]);
  }
  return combined_pattern;
}