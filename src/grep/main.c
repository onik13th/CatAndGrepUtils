#include "../common/flag_struct.h"
#include "parser/flag_parser.h"
#include "controller/grep_main_controller.h"

int main(int argc, char *argv[]) {
  GrepFlags flags = grep_parse_flags(argc, argv);
  grep(argc, argv, flags);
  return 0;
}