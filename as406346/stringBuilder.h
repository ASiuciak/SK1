/*
 * Interfejs przechowujący napisy.
 */

#ifndef STRINGBUILDER_H
#define STRINGBUILDER_H

#include <stddef.h>
#include <stdbool.h>

/*
 * Struktura przechowująca słowa.
 */
struct stringBuilder {
    char *word; /**< właściwe słowo */
    size_t length; /**< długość słowa */
    size_t capacity; /**< ilosć pamięci atualnie zaalokowanej na słowo */
};

/*
 * Nowy typ String - wskaźnik na strukturę typu stringBuilder.
 */
typedef struct stringBuilder *String;

/* Tworzy nowy obiekt typu String, kończy program z kodem błędu 1
 * przy nieudanej alokacji pamięci.
 */
String newString();

/* Alokuje pamięć na dodatkowe znaki (o ile to konieczne).
 * Zwraca false, jeśli alokacja się nie udała, true w przeciwnym wypadku.
 */
bool ensureSpace(String s, size_t addLen);

/* Dopisuje znak na końcu słowa przechowywanego w danej strukturze String.
 * Zwraca false, jeśli alokacja się nie udała, true w przeciwnym wypadku.
 */
bool append(String s, char c);

// Wypisuje na standardowe wyjście słowo trzymane w strukturze String.
void printString(String s);

// Zwalnia pamięć zaalokowaną na strukturę String i słowo w niej trzymane.
void freeString(String s);

// Odcina daną liczbę znaków z końca słowa.
void cutLastCharacters(String s, size_t howMany);

/* Dopisuje słowo w postaci Cstring
 * na końcu słowa przechowywanego w danej strukturze String.
 * Zwraca false, jeśli alokacja się nie udała, true w przeciwnym wypadku.
 * UWAGA! Nie zwalnia pamięci zaalokowanej na argument add
 */
bool appendCString(String s, char *add);

/* Łączy 2 słowa przechowywane w strukturach String w jedno.
 * Dopisuje słowo add na końcu słowa s.
 * Całe słowo zostaje zapisane w s, pamięć zaalokowana na add
 * zostaje zwolniona.
 * Zwraca false, jeśli alokacja się nie udała, true w przeciwnym wypadku.
 */
bool appendString(String s, String add);

#endif // STRINGBUILDER_H
