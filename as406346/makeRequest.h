/*
 * Interfejs funkcji odpowiedzialnych za tworzenie żądania HTTP.
 */

#include <stdio.h>
#include <stdlib.h>
#include "stringBuilder.h"

/* Tworzy żądanie HTTP typu GET z podanym adresem testowym, hostem
 * i ciasteczkami. (jesli nie ma ciasteczek, powstaje żądanie bez pola
 * "Cookies: ")
 */
String makeRequest(char *testedAddress, char *host, String cookies);
