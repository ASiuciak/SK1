/*
 * Interfejs funkcji odpowiedzialnych za odczyt pliku z ciasteczkami.
 */

#ifndef READCOOKIES_H
#define READCOOKIES_H

#include "stringBuilder.h"
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define ENDL 10
#define CR 13

/* Odczytuje i zapisuje 1 linijkę z podanego pliku.
 * Zwraca strukturę String przechowującą daną linijkę,
 * kończy program w razie nieudanej alokacji pamięci.
 */
String readLine(FILE *file);

/* Odzcytuje i zapisuje całą zawartość pliku z ciasteczkami,
 * w formacie key1=value1; key2=value2; ...
 */
String readAll(FILE *file);

#endif //READCOOKIES_H
