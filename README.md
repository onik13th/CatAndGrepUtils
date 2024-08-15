# CatAndGrepUtils

## Описание
Этот проект реализует две популярные командные утилиты: cat и grep. Эти инструменты предназначены для работы с текстовыми файлами и строками в командной строке.

my_cat — это реализация утилиты cat, которая выводит содержимое одного или нескольких файлов на стандартный вывод. Она поддерживает различные флаги для изменения поведения вывода:

    -b — нумерация непустых строк.

    -e — отображение символа конца строки $ и включение вывода непечатаемых символов.

    -n — нумерация всех строк.

    -s — сжатие нескольких пустых строк в одну.

    -t — отображение табуляций как ^I и включение вывода непечатаемых символов.

    -v — вывод непечатаемых символов в виде кареток, за исключением табуляций и конца строки.

    -E — отображение символа конца строки $.

    -T — отображение табуляций как ^I.
    
my_grep — это реализация утилиты grep, которая ищет строки, соответствующие шаблону, в одном или нескольких файлах и выводит их на стандартный вывод. Утилита поддерживает следующие флаги:

-i — игнорирование регистра при сопоставлении.
-v — инвертирование совпадений (вывод всех строк, которые не соответствуют шаблону).
-c — вывод только количества строк, соответствующих шаблону.
-l — вывод только имен файлов, содержащих соответствующие строки.
-n — вывод номеров строк перед совпадающими строками.
-o — вывод только тех частей строк, которые соответствуют шаблону.
-h — отключение вывода имен файлов перед соответствующими строками.

Чтобы собрать проект, перейдите в директории cat и grep соответственно и выполните следующию команду в терминале:
 make all

Эти команды скомпилируют исполняемые файлы my_cat и my_grep.

Использование
my_cat
    ./my_cat [опции] [файлы...]

my_grep
    ./my_grep [опции] шаблон [файлы...]

Тестирование
В проект включены автоматизированные тесты для проверки корректности работы обеих утилит. Тесты можно запустить, используя следующую цель:
    make tests
Этот скрипт проверяет работу утилит на различных тестовых файлах и с различными флагами, обеспечивая соответствие поведения оригинальным утилитам cat и grep.
    
Авторы
Разработано Борун Давидом в качестве проектного обучения.