#include "file_handler.h"

// функция управляет чтением и обработкой файлов, включая применение различных
// флагов и форматирование вывода.
void cat_file(FILE *file, CatFlags flags, const char *table[static 256]) {
  int c = 0;
  int last = '\n';
  int line_number = 1;  // для -b и -n
  bool squeeze = false;

  if (flags.symbolEndl) {
    cat_set_endl(table);
  }
  if (flags.tab) {
    cat_set_tab(table);
  }
  if (flags.printNonPrintable) {
    cat_set_non_printble(table);
  }

  while ((c = fgetc(file)) != EOF) {
    if (last == '\n') {
      if (flags.squeezeBlank && c == '\n') {
        if (squeeze) {
          continue;
        }

        squeeze = true;
      } else {
        squeeze = false;
      }

      if (flags.numNonBlank) {
        if (c != '\n') {
          printf("%6i\t", line_number++);
        } else if (c == '\n' && flags.symbolEndl) {
          printf("%6s\t", "");
        }
      } else if (flags.numAll) {
        printf("%6i\t", line_number++);
      }
    }

    // Обработка таблицы символов (`table`):
    // Использует предоставленную таблицу символов для специальной обработки
    // каждого символа (например, для замены табуляции на "^I" или вывода
    // непечатаемых символов в видимом формате).

    if (!*table[c]) {
      printf("%c", '\0');  // для корректного вывода бинарного файла
    } else {
      printf("%s", table[c]);
      last = c;
    }
  }
}