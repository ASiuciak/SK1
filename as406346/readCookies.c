#include "readCookies.h"

String readLine(FILE *file) {
    String s = newString();
    int c = fgetc(file);
    bool trouble = false;
    while (c != EOF && c != ENDL && c != CR && !trouble) {
        if (!append(s, (char)c)) {
            trouble = true;
        }
        c = fgetc(file);
    }
    if (trouble) {
        fprintf(stderr, "Bad alloc\n");
        exit(1);
    }
    while (c != ENDL && c != EOF) {
        c = fgetc(file);
    }
    return s;
}

String readAll(FILE *file) {
    String s = newString();
    bool end = false, trouble = false;
    while (!end) {
        String line = readLine(file);
        if (line->length == 0) {
            end = true;
        }
        if (!appendString(s, line)) {
            trouble = true;
        }
        if (!end) {
            if (!appendCString(s, "; ")) {
                trouble = true;
            }
        }
    }
    if (trouble) {
        fprintf(stderr, "Bad alloc\n");
        exit(1);
    }
    cutLastCharacters(s, 2);
    return s;
}
