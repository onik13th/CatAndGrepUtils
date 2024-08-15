CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TARGET_1 = my_grep
TEST = integration_tests.sh

all: $(TARGET_1)

$(TARGET_1):
	$(CC) $(CFLAGS) main.c handler/file_handler.c controller/grep_main_controller.c flags/grep_flags.c parser/flag_parser.c -o $(TARGET_1)

tests:
	./$(TEST)

rebuild: 
	make clean 
	make all 

format:
	clang-format -style=google -n */*.c */*.h 
	sleep 1
	reset
	clang-format -style=google -i */*.c */*.h 
	clang-format -style=google -n */*.c */*.h 

memory: 
	valgrind -s --track-origins=yes --leak-check=full ./$(TEST)

clean:
	rm -rf my_grep