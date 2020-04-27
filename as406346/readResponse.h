/*
 * Interfejs funkcji służacych do odczytywania
 * odpowiednich danych z odpowiedzi serwera HTTP.
 */

#include "stringBuilder.h"
#include <stdio.h>
#include <stdlib.h>

// Oblicza  n-tą potęga liczby a.
size_t power(size_t a, size_t n);

// Sprawdza, czy dany znak jest cyfrą.
bool isDigit(char c);

/* Sprawdza, czy dany znak może należeć do reprezentacji liczby
 * w systemie szesnastkowym (cyfra lub małe liery z zakresu 'a' - 'f').
 */
bool isHexDigit(char c);

/* Wydziela z linijki "Content-Length: " z odpowiedzi serwera HTTP
 * fragment reprezentujący liczbę będacą długością zasobu.
 */
String getContentLength(String line);

/* Przekształca słowo reprezentujące liczbę w systemie dziesiętnym
 * na liczbę. Wykorzystywana do odkodowania wartości z pola
 * "Content-Length: ".
 */
size_t getDecimalLength(String num);

/* Sprawdza, czy dana linijka zawiera poprawną reprezentację
 * długości części zasobu (liczba w systemie szesnastkowym +
 * '\r' na końcu linii)
 */
bool isChunkLength(String line);

/* Przekształca słowo reprezentujące liczbę w systemie szesnastkowym
 * na liczbę. Wykorzystywana do odkodowania długości części zasobu.
 * Przyjmuję, że argument nie zawiera już znaku '\r' na końcu.
 */
size_t getChunkLength(String line);

// Odczytuje i zapisuje 1 ciasteczko z pola "Set-Cookie: "
String getCookie(String line); 
