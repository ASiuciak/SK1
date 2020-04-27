#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stringBuilder.h"

/* Przyjęta przeze mnie początkowa ilość pamięci do
 * zaalokowania na nowe słowo.
 */
const size_t init_cap = 2;

String newString() {
    String n = malloc(sizeof(struct stringBuilder));
    if (n == NULL) {
        fprintf(stderr, "Bad alloc\n");
        exit(1);
    }

    n->word = malloc(init_cap);
    if (n->word == NULL) {
        fprintf(stderr, "Bad alloc\n");
        exit(1);
    }

    *n->word = '\0';
    n->capacity = init_cap;
    n->length = 0;
    return n;
}

bool ensureSpace(String s, size_t addLen) {
    if (s == NULL) { return false; }
    if (addLen == 0) { return true; }

    if (s->capacity >= s->length + addLen + 1) { return true; }

    while (s->capacity < s->length + addLen + 1) {
        s->capacity *= 2;
        if (s->capacity == 0) {
            s->capacity--;
        }
    }
    s->word = realloc(s->word, s->capacity);
    if (s->word == NULL) { return false; }
    return true;
}

bool append(String s, char c) {
    if (s == NULL) { return false; }
    if (!ensureSpace(s, 1)) { return false; }
    s->word[s->length] = c;
    s->length++;
    s->word[s->length] = '\0';
    return true;
}

void printString(String s) {
    if (s != NULL && s->word != NULL) {
        printf("%s\n", s->word);
    }
}

void freeString(String s) {
    if (s != NULL) {
        if (s->word != NULL) {
            free(s->word);
        }
        free(s);
    }
}

void cutLastCharacters(String s, size_t howMany) {
    if (s != NULL && s->word != NULL && howMany <= s->length) {
        s->word[s->length - howMany] = '\0';
        s->length -= howMany;
    }
}

bool appendCString(String s, char *add) {
    if (s == NULL || add == NULL) { return false; }
    size_t len = strlen(add);
    if (len == 0) { return true; }
    bool trouble = false;
    for (size_t i = 0; i < len && !trouble; i++) {
        if (!append(s, add[i])) {
            trouble = true;
        }
    }
    return !trouble;
}

bool appendString(String s, String add) {
    if (add == NULL) { return false; }
    bool res = appendCString(s, add->word);
    freeString(add);
    return res;
}
