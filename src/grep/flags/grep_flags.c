#include "grep_flags.h"

void grep_counter(FILE *file, GrepFlags flags, char const *filename,
                  regex_t *preg, int count_file) {  // -c
  char *line = 0;
  size_t length = 0;
  regmatch_t match;
  int count = 0;

  while (getline(&line, &length, file) > 0) {
    if (!regexec(preg, line, 1, &match, 0)) {
      count++;
    }
  }

  if (count_file == 1 || flags.suppressFileNames) {
    printf("%i\n", count);
  } else if (count_file > 1 && !flags.suppressFileNames) {
    printf("%s:%i\n", filename, count);
  }

  free(line);
}

void print_matching_files(FILE *file, const char *filename,
                          regex_t *preg) {  // -f
  char *line = NULL;
  size_t length = 0;
  regmatch_t match;

  while (getline(&line, &length, file) > 0) {
    if (!regexec(preg, line, 1, &match, 0)) {
      printf("%s\n", filename);
      free(line);
      return;  // выводим имя файла и завершаем функцию после первого совпадения
    }
  }
  free(line);  // освобождаем ресурсы, если не найдено совпадений
}

void print_matched_part(char *line, const char *filename, regex_t *preg,
                        regmatch_t match, int count_file, int line_number,
                        GrepFlags flags) {  // -o
  const char *ptr = line;
  while (!regexec(preg, ptr, 1, &match, (ptr == line) ? 0 : REG_NOTBOL)) {
    int print_length = match.rm_eo - match.rm_so;

    if (count_file > 1 && !flags.suppressFileNames) {
      printf("%s:", filename);
    }
    if (flags.numberOfLine) {
      printf("%d:", line_number);
    }

    printf("%.*s\n", print_length,
           ptr + match.rm_so);  // ширина в int, указатель на начало совпадения
    ptr += match.rm_eo;  // перемещаем указатель на конец последнего совпадения
  }
}

void init_flags(GrepFlags *flags) {
  flags->num_patterns = 0;  // начальное кол-во шаблонов
  flags->capacity = 10;     // начальная вместимость
  flags->patterns = malloc(flags->capacity * sizeof(char *));
  if (!flags->patterns) {
    fprintf(stderr, "Failed to allocate memory for patterns\n");
    exit(EXIT_FAILURE);
  }
}

void free_flags(GrepFlags *flags) {
  for (int i = 0; i < flags->num_patterns; i++) {
    free(flags->patterns[i]);
  }
  free(flags->patterns);
}

void add_pattern(GrepFlags *flags, const char *pattern) {
  if (flags->num_patterns == flags->capacity) {
    int new_capacity = flags->capacity * 2;
    char **new_patterns =
        realloc(flags->patterns, new_capacity * sizeof(char *));
    if (!new_patterns) {
      fprintf(stderr, "Failed to reallocate memory for patterns\n");
      free_flags(flags);
      exit(EXIT_FAILURE);
    }
    flags->patterns = new_patterns;
    flags->capacity = new_capacity;
  }
  flags->patterns[flags->num_patterns++] = strdup(pattern);
}

void load_patterns_from_file(GrepFlags *flags, const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "Cannot open pattern file: %s\n", filename);
    exit(EXIT_FAILURE);
  }

  char *line = NULL;
  size_t length = 0;
  ssize_t read;

  while ((read = getline(&line, &length, file)) != -1) {
    // удаляется символ новой строки, если он присутствует
    if (line[read - 1] == '\n') {
      line[read - 1] = '\0';
    }
    add_pattern(flags, line);
  }

  free(line);
  fclose(file);
}