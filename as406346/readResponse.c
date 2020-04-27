#include "readResponse.h"

size_t power(size_t a, size_t n) {
    size_t result = 1;
    for (size_t i = 0; i < n; i++) {
        result = result * a;
    }
    return result;
}

bool isDigit(char c) {
    return ((int)c >= 48 && (int)c <= 57);
}

bool isHexDigit(char c) {
    return isDigit(c) || ((int)c >= 97 && (int)c <= 102);
}

String getContentLength(String line) {
    size_t mark = 16; // "Content-Length: " zawiera 16 znaków
    String result = newString();
    while (mark < line->length && isDigit(line->word[mark])) {
        if (!append(result, line->word[mark])) {
            fprintf(stderr, "ERROR: Bad alloc\n");
            exit(1);
        }
        mark++;
    }
    return result;
}

size_t getDecimalLength(String num) {
    if (num == NULL || num->word == NULL) { return 0; }
    size_t p = num->length - 1;
    size_t result = 0;
    for (size_t i = 0; i < num->length; i++) {
        size_t a = num->word[i] - '0';
        result += a * power(10, p);
        p--;
    }
    return result;
}

bool isChunkLength(String line) {
    cutLastCharacters(line, 1);
    if (line->length == 0) { return false; }
    bool ok = true;
    for (size_t i = 0; i < line->length && ok; i++) {
        if (!isHexDigit(line->word[i])) { ok = false; }
    }
    return ok;
}

size_t getChunkLength(String line) {
    if (line == NULL || line->word == NULL) { return 0; }
    size_t p = line->length - 1;
    size_t result = 0;
    for (size_t i = 0; i < line->length; i++) {
        size_t a;
        if (!isDigit(line->word[i])) {
            a = (size_t)((int)line->word[i] - 'a' + 10);
        } else {
            a = line->word[i] - '0';
        }
        result += a * power(16, p);
        p--;
    }
    return result;
}

String getCookie(String line) {
    if (line == NULL || line->word == NULL || line->length < 13) {
        return NULL;
    }
    size_t mark = 12; //"Set-Cookie: " ma 12 znaków
    String result = newString();
    while (mark < line->length && line->word[mark] != ';' &&
          line->word[mark] != '\r' && line->word[mark] != '\n') {
        if (!append(result, line->word[mark])) {
            fprintf(stderr, "ERROR: Bad alloc\n");
            exit(1);
        }
        mark++;
    }
    return result;
}
