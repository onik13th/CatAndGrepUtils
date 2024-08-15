#ifndef FLAG_STRUCT_H
#define FLAG_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

typedef struct {
  bool numNonBlank;        // -b
  bool symbolEndl;         // -e
  bool numAll;             // -n
  bool squeezeBlank;       // -s
  bool tab;                // -t
  bool printNonPrintable;  // -v
} CatFlags;

typedef struct {
  char **patterns;  // динамический массив для хранения шаблонов
  int num_patterns;           // количество шаблонов
  int capacity;               // вместимость массива
  int regex_flag;             // для регулярных выражений
  bool invertMatch;           // -v
  bool counter;               // -c
  bool listMatchingFiles;     // -l
  bool numberOfLine;          // -n
  bool printMatched;          // -o
  bool suppressFileNames;     // -h
  bool suppressErrorMessage;  // -s
} GrepFlags;

#endif