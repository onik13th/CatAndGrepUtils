#include "flag_parser.h"

CatFlags cat_parse_flags(int argc, char *argv[]) {
  struct option longOptions[] = {{"number-nonblank", 0, NULL, 'b'},
                                 {"number", 0, NULL, 'n'},
                                 {"squeeze-blank", 0, NULL, 's'},
                                 {NULL, 0, NULL, 0}};

  CatFlags flags = {false};

  int current_flag = 0;

  while ((current_flag =
              getopt_long(argc, argv, "benstvET", longOptions, NULL)) != -1) {
    switch (current_flag) {
      case 'b':
        flags.numNonBlank = true;
        break;
      case 'e':
        flags.symbolEndl = true;
        flags.printNonPrintable = true;
        break;
      case 'v':
        flags.printNonPrintable = true;
        break;
      case 'E':
        flags.symbolEndl = true;
        break;
      case 'n':
        flags.numAll = true;
        break;
      case 's':
        flags.squeezeBlank = true;
        break;
      case 't':
        flags.tab = true;
        flags.printNonPrintable = true;
        break;
      case 'T':
        flags.tab = true;
        break;
      case '?':  // неизвестный флаг
        fprintf(stderr, "usage: my_cat [-benstvET] [file ...]\n");
        exit(EXIT_FAILURE);
    }
  }

  return flags;
}