CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET_1 = s21_cat
FLAG_PARSER_C = flag_parser.c

all: $(TARGET_1)

$(TARGET_1): 
	$(CC) $(CFLAGS) -o $(TARGET_1) main.c cat_flags.c cat_file_handler.c cat_main_controller.c $(FLAG_PARSER_C)

rebuild: 
	make clean 
	make all

clean:
	rm -rf s21_cat