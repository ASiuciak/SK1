#include "makeRequest.h"

String makeRequest(char *testedAddress, char *host, String cookies) {
    if (testedAddress == NULL || host == NULL) { return NULL; }
    String result = newString();
    if (!appendCString(result, "GET  ")) {
        fprintf(stderr, "ERROR: Bad alloc\n");
        exit(1);
    }
    if (!appendCString(result, testedAddress)) {
        fprintf(stderr, "ERROR: Bad alloc\n");
        exit(1);
    }
    if (!appendCString(result, " HTTP/1.1\r\nHost: ")) {
        fprintf(stderr, "ERROR: Bad alloc\n");
        exit(1);
    }
    if (!appendCString(result, host)) {
        fprintf(stderr, "ERROR: Bad alloc\n");
        exit(1);
    }
    if (cookies != NULL && cookies->word != NULL && cookies->length > 0) {
        if (!appendCString(result, "\r\nCookies: ")) {
            fprintf(stderr, "ERROR: Bad alloc\n");
            exit(1);
        }
        if (!appendString(result, cookies)) {
            fprintf(stderr, "ERROR: Bad alloc\n");
            exit(1);
        }
    } else {
        freeString(cookies);
    }
    if (!appendCString(result, "\r\nConnection: close\r\n\r\n")) {
        fprintf(stderr, "ERROR: Bad alloc\n");
        exit(1);
    }
    return result;
}
