#!/bin/bash

# Определение цветов
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color - для возвращения к стандартному цвету терминала

function prepare_test_files {
    # Создаем тестовые файлы
    echo -n "" > empty.txt
    echo -e "Test\nText" > simple.txt
    echo -e "Text\tText\n\n\n\nNew Line\n\t!@#\r\r\r@#df\v$%^&*()\r\v" > special_chars.txt
}

# Функция для запуска теста
function run_test {
  file=$1
  echo "Testing with file: $file"

  # Запускаем вашу программу и стандартную cat
  ./my_cat $file > output_my_cat.txt
  cat $file > output_cat.txt

  # Сравниваем выходные данные
  if diff output_my_cat.txt output_cat.txt > /dev/null; then
    echo -e "  ${GREEN}PASS:${NC} Output matches for file $file"
  else
    echo -e "  ${RED}FAIL:${NC} Output does not match for file $file"
  fi
}

# Функция для запуска теста с флагами
function run_test_with_flags {
  file=$1
  flag=$2
  echo "Testing file: $file with flag: $flag"

  # Запускаем вашу программу и стандартную cat с указанным флагом
  ./my_cat $flag $file > output_my_cat.txt
  cat $flag $file > output_cat.txt

  # Сравниваем выходные данные
  if diff output_my_cat.txt output_cat.txt > /dev/null; then
    echo -e "  ${GREEN}PASS:${NC} Output matches for file $file with flag $flag"
  else
    echo -e "  ${RED}FAIL:${NC} Output does not match for file $file with flag $flag"
    echo -e "  Diff output:"
    diff output_my_cat.txt output_cat.txt
  fi
}

function test_multiple_files {
    echo "Testing with multiple files"

    # Тестирование с двумя файлами
    echo "Testing with two files: simple.txt and special_chars.txt"
    ./my_cat simple.txt special_chars.txt > output_my_cat_two_files.txt
    cat simple.txt special_chars.txt > output_cat_two_files.txt

    if diff output_my_cat_two_files.txt output_cat_two_files.txt > /dev/null; then
        echo -e "  ${GREEN}PASS:${NC} Output matches for two files"
    else
        echo -e "  ${RED}FAIL:${NC} Output does not match for two files"
        echo -e "  Diff output:"
        diff output_my_cat_two_files.txt output_cat_two_files.txt
    fi

    # Тестирование с тремя файлами
    echo "Testing with three files: empty.txt, simple.txt, and special_chars.txt"
    ./my_cat empty.txt simple.txt special_chars.txt > output_my_cat_three_files.txt
    cat empty.txt simple.txt special_chars.txt > output_cat_three_files.txt

    if diff output_my_cat_three_files.txt output_cat_three_files.txt > /dev/null; then
        echo -e "  ${GREEN}PASS:${NC} Output matches for three files"
    else
        echo -e "  ${RED}FAIL:${NC} Output does not match for three files"
        echo -e "  Diff output:"
        diff output_my_cat_three_files.txt output_cat_three_files.txt
    fi
}

# Тестируем для каждого файла
function test_basic_functionality {
    for file in "${files[@]}"; do
      run_test $file
    done
}

# Тестируем для каждого файла с каждым флагом
function test_with_flags {
    for file in "${files[@]}"; do
      for flag in "${flags[@]}"; do
        run_test_with_flags $file $flag
      done
    done
}

# Тест на несуществующий файл
function test_non_existing_file {
    echo "Testing with non-existing file"
    ./my_cat non_existing_file.txt > output_my_cat_nonexist.txt 2>&1
    cat non_existing_file.txt > output_cat_nonexist.txt 2>&1

    ./my_cat $file 2>&1 | sed 's/^s21_cat: //' > output_my_cat_nonexist.txt
    cat $file 2>&1 | sed 's/^cat: //' > output_cat_nonexist.txt

    if diff output_my_cat_nonexist.txt output_cat_nonexist.txt > /dev/null; then
      echo -e "  ${GREEN}PASS:${NC} Error messages match for non-existing file"
    else
      echo -e "  ${RED}FAIL:${NC} Error messages do not match for non-existing file"
    fi
}
echo -e "\n"

# Тест на случай без указания файла (стандартный ввод)
function test_standard_input {
    echo "Testing with standard input"
    echo "Example input" | ./my_cat > output_my_cat_stdin.txt
    echo "Example input" | cat > output_cat_stdin.txt

    if diff output_my_cat_stdin.txt output_cat_stdin.txt > /dev/null; then
      echo -e "  ${GREEN}PASS:${NC} Output matches for standard input"
    else
      echo -e "  ${RED}FAIL:${NC} Output does not match for standard input"
    fi
}

function test_binary_file {
    echo "Testing with binary file: image.bin"

    # Создаем бинарный файл для тестирования
    dd if=/dev/urandom of=image.bin bs=1M count=1 2> /dev/null

    # Запускаем вашу программу и стандартную cat
    ./my_cat image.bin > output_my_cat_binary.txt
    cat image.bin > output_cat_binary.txt

    # Сравниваем выходные данные
    if diff output_my_cat_binary.txt output_cat_binary.txt > /dev/null; then
        echo -e "  ${GREEN}PASS:${NC} Output matches for binary file"
    else
        echo -e "  ${RED}FAIL:${NC} Output does not match for binary file"
        echo -e "  Diff output:"
        diff output_my_cat_binary.txt output_cat_binary.txt
    fi

    # Удаляем тестовый бинарный файл
    rm -rf image.bin
}

function test_non_existing_flags {
    echo "Testing with non-existing flags: -xyz"

    # Запускаем вашу программу с несуществующими флагами
    if ./my_cat -xyz simple.txt 2> output_my_cat_invalid_flags.txt; then
        echo -e "  ${RED}FAIL:${NC} Program did not terminate with error on invalid flags"
    else
        echo -e "  ${GREEN}PASS:${NC} Program terminated with error on invalid flags"
        cat output_my_cat_invalid_flags.txt
    fi
}

function test_long_flags {
    echo "Testing long flags for functionality"
    local long_flags=("--number-nonblank" "--number" "--squeeze-blank")
    local short_flags=("-b" "-n" "-s")

    for i in "${!long_flags[@]}"; do
        local long_flag="${long_flags[$i]}"
        local short_flag="${short_flags[$i]}"
        for file in "${files[@]}"; do
            echo "Testing ${long_flag} and ${short_flag} with file: $file"

            ./my_cat $long_flag $file > output_my_cat_long.txt
            ./my_cat $short_flag $file > output_my_cat_short.txt
            cat $short_flag $file > output_cat.txt

            # Compare long flag output against short flag output
            if diff output_my_cat_long.txt output_cat.txt > /dev/null; then
                echo -e "  ${GREEN}PASS:${NC} Output matches for $long_flag"
            else
                echo -e "  ${RED}FAIL:${NC} Output does not match for $long_flag"
                echo "  Diff output:"
                diff output_my_cat_long.txt output_cat.txt
            fi

            # Clean up
            rm output_my_cat_long.txt output_my_cat_short.txt output_cat.txt
        done
    done
}

function cleanup_files {
    rm -rf empty.txt simple.txt special_chars.txt output_*.txt my_cat
}

# Компиляция программы
gcc -Wall -Wextra -Werror -std=c11 -o my_cat main.c flags/cat_flags.c parser/flag_parser.c handler/file_handler.c controller/cat_main_controller.c || { echo "Compilation failed"; exit 1; }

# Определяем тестовые файлы
declare -a files=("empty.txt" "simple.txt" "special_chars.txt")
# Определяем флаги для тестирования
declare -a flags=("-b" "-e" "-n" "-s" "-t" "-v" "-bestv" "-enstv" "-benstv" "-bes" "-enst")

# Подготовка тестовых файлов
prepare_test_files

# Запуск всех тест-кейсов
test_basic_functionality
echo -e "\n"
test_with_flags
echo -e "\n"
test_multiple_files 
echo -e "\n"
test_non_existing_file
echo -e "\n"
test_standard_input
echo -e "\n"
test_binary_file
echo -e "\n"
test_non_existing_flags
echo -e "\n"
test_long_flags
echo -e "\n"

# Очистка
cleanup_files