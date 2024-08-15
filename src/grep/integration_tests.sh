#!/bin/bash

# Определение цветов
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color - для возвращения к стандартному цвету терминала

# компиляция программы
function compile() {
    gcc -Wall -Wextra -Werror -std=c11 -o my_grep main.c handler/file_handler.c controller/grep_main_controller.c flags/grep_flags.c parser/flag_parser.c || { echo "Compilation failed"; exit 1; }
    echo "Compilation successful"
}

# очистка созданных файлов
function cleanup_files() {
    echo "Cleaning up..."
    rm -f my_grep
    rm -f test_output.txt
    rm -f pattern.txt
    rm -f test*.txt
    rm -f sys_output.txt
    rm -f my_output.txt
}

# функция для запуска и сравнения вывода ./s21_grep и системного grep
function run_test() {
    local pattern="$1"
    local flags="$2"
    local files="$3"

    echo "Running test with pattern: '$pattern', flags: '$flags', files: '$files'"

    eval "./my_grep $flags '$pattern' $files > my_output.txt"
    eval "grep $flags '$pattern' $files > sys_output.txt"

    if diff -u my_output.txt sys_output.txt; then
        echo -e "${GREEN}TEST PASSED!${NC}"
    else
        echo -e "${RED}TEST FAILURE!${NC}"
    fi
}

# создание тестовых файлов
function create_test_files() {
    echo "First line" > test1.txt
    echo "Second line" > test2.txt
    echo "Third line" > test3.txt
    echo "Fourth line" > test4.txt
    echo "just line" > pattern.txt
}

# Тестирование различных случаев
function run_tests() {
    create_test_files

    # тест без флагов
    run_test "line" "" "test1.txt test2.txt"

    # тесты с каждым флагом по отдельности
    run_test "LINE" "-i" "test1.txt test2.txt"
    run_test "line" "-v" "test1.txt test2.txt"
    run_test "line" "-c" "test1.txt test2.txt"
    run_test "line" "-l" "test1.txt test2.txt"
    run_test "line" "-n" "test1.txt test2.txt"
    run_test "line" "-o" "test1.txt test2.txt"
    run_test "line" "-h" "test1.txt test2.txt"
    run_test "line" "-s" "test1.txt test6.txt"
    run_test "-e line -e Second -e Third" "" "test1.txt test2.txt test3.txt"
    run_test "-f pattern.txt" "" "test1.txt test2.txt"

    # тесты с комбинациями флагов
    run_test "line" "-on" "test1.txt test2.txt"
    run_test "line" "-onv" "test1.txt test2.txt"
    run_test "LInE" "-onvi" "test1.txt test2.txt"
    run_test "line" "-co" "test1.txt test2.txt"
    run_test "line" "-vo" "test1.txt test2.txt"
    run_test "line" "-von" "test1.txt test2.txt"
    run_test "LInE" "-voni" "test1.txt test2.txt"
    run_test "line" "-ho" "test1.txt test2.txt"
    run_test "line" "-hn" "test1.txt test2.txt"
    run_test "LInE" "-hni" "test1.txt test2.txt"
    run_test "-e line -e SeConD -e Third" "-oin" "test1.txt test2.txt test3.txt"

    # тесты с несколькими файлами
    run_test "line" "" "test1.txt test2.txt test3.txt pattern.txt"

    # тест с несуществующим файлом
    run_test "line" "" "nofile.txt"

    # тесты с существующими и несуществующими файлами
    run_test "line" "" "test1.txt nofile.txt test2.txt"

    # очистка
    cleanup_files
}

# основная логика скрипта
compile
run_tests