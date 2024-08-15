#include "../common/flag_struct.h"
#include "controller/cat_main_controller.h"
#include "flags/cat_flags.h"
#include "parser/flag_parser.h"

// argc - счетчик количества параметров командой строки argc.
// argv - значения парамеров командной строки argv[].

int main(int argc, char *argv[]) {
  CatFlags flags = cat_parse_flags(argc, argv);
  const char *table[256];
  cat_set_table(table);
  cat(argc, argv, flags, table);
  return 0;
}