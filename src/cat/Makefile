CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET_1 = my_cat
FLAG_PARSER_C = parser/flag_parser.c
TEST = integration_tests.sh

all: $(TARGET_1)

$(TARGET_1): 
	$(CC) $(CFLAGS) -o $(TARGET_1) main.c flags/cat_flags.c handler/file_handler.c controller/cat_main_controller.c $(FLAG_PARSER_C)

rebuild: 
	make clean 
	make all

tests:
	./$(TEST)


format:
	clang-format -style=google -n */*.c */*.h 
	sleep 1
	reset
	clang-format -style=google -i */*.c */*.h 
	clang-format -style=google -n */*.c */*.h 

memory: 
	valgrind -s --track-origins=yes --leak-check=full ./$(TEST)

clean:
	rm -rf my_cat

