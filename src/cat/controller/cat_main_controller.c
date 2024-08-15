#include "cat_main_controller.h"

void cat(int argc, char *argv[], CatFlags flags,
         const char *table[static 256]) {
  bool has_files = false;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {  // argv[i][0] это первый символ i-й строки
      FILE *file = fopen(argv[i], "rb");
      if (!file) {
        fprintf(stderr, "s21_cat: %s: No such file or directory\n", argv[i]);
        exit(EXIT_FAILURE);  // Завершаем программу с кодом ошибки
      }
      has_files = true;
      cat_file(file, flags, table);
      fclose(file);
    }
  }
  
  if (!has_files) {
    cat_file(stdin, flags, table);
  }
}