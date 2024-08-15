#include "flag_parser.h"

GrepFlags grep_parse_flags(int argc, char *argv[]) {
  GrepFlags flags = {0};
  init_flags(&flags);

  int current_flag = 0;
  while ((current_flag = getopt_long(argc, argv, "e:ivclnohsf:", NULL, NULL)) !=
         -1) {
    switch (current_flag) {
      case 'e':
        flags.regex_flag |= REG_EXTENDED;
        add_pattern(&flags, optarg);
        break;
      case 'i':
        flags.regex_flag |= REG_ICASE;
        break;
      case 'v':
        flags.invertMatch = true;
        break;
      case 'c':
        flags.counter = true;
        break;
      case 'l':
        flags.listMatchingFiles = true;
        break;
      case 'n':
        flags.numberOfLine = true;
        break;
      case 'o':
        flags.printMatched = true;
        break;
      case 'h':
        flags.suppressFileNames = true;
        break;
      case 's':
        flags.suppressErrorMessage = true;
        break;
      case 'f':
        flags.regex_flag |= REG_EXTENDED;
        load_patterns_from_file(&flags, optarg);
        break;
      case '?':
        fprintf(
            stderr,
            "usage: my_grep [-ivclnoh] [-e pattern] [pattern] [file ...]\n");
        exit(EXIT_FAILURE);
      default:
        fprintf(stderr, "unknown err");
        exit(EXIT_FAILURE);
    }
  }

  if (flags.num_patterns == 0 &&
      optind < argc) {  // добавляем шаблон, если он не был задан через -e
    add_pattern(&flags, argv[optind++]);
  }

  return flags;
}