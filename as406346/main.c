#include <arpa/inet.h>
#include <assert.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <stdarg.h>
#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <stdint.h>
#include "readCookies.h"
#include "readResponse.h"
#include "makeRequest.h"

#define MAXLINE 1000
#define SA struct sockaddr

int main(int argc, char** argv) {
    int sockfd; // nr gniazda
    struct addrinfo addrHints; // wskazówki o adresie dla getaddrinfo
    struct addrinfo *addrResult; // wynik wywołania getaddrinfo
    char recvline[MAXLINE + 10];

    // Sprawdzamy, czy podano prawidłową liczbę argumentów.
    if (argc != 4) {
        fprintf(stderr, "ERROR: Usage: %s <server address>:<port> <cookies file> <tested address>\n", argv[0]);
        exit(1);
    }

    // Oddzielamy adres hosta od portu w pierszym argumencie.
    char *hostPort = argv[1];
    if (strchr(hostPort, ':') == NULL) {
        fprintf(stderr, "ERROR: First paramter should be like <server address>:<port>\n");
        exit(1);
    }
    char delim[] = ":";
    char *ptr = strtok(hostPort, delim);
    char *host;
    char *port;

    host = ptr;
    ptr = strtok(NULL, delim);
    port = ptr;

    // Szukamy podanego adresu po nazwie i numerze portu.
    memset(&addrHints, 0, sizeof(struct addrinfo));
    addrHints.ai_family = AF_INET;
    addrHints.ai_socktype = SOCK_STREAM;
    addrHints.ai_protocol = IPPROTO_TCP;
    int err = getaddrinfo(host, port, &addrHints, &addrResult);
    if (err != 0) {
        fprintf(stderr, "ERROR: addres not found\n");
        exit(1);
    }

    // Sprawdzamy, czy podano prawidłowy plik z ciasteczkami.
    char *f = argv[2];
    FILE *file = fopen(f, "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: Can't read a cookies file.\n");
        exit(1);
    }

    // Ostatni argument to adres to testowania, dodajemy go do żadąnia HTTP.
    char *testedAddress = argv[3];


    // Tworzymy gniazdo i łączymy się z serwerem.
    sockfd = socket(addrResult->ai_family, addrResult->ai_socktype,
                    addrResult->ai_protocol);
    if (sockfd < 0) {
        printf("ERROR: socket\n");
        exit(1);
    }
    if (connect(sockfd, addrResult->ai_addr, addrResult->ai_addrlen) < 0) {
        printf("ERROR: connection\n");
        exit(1);
    }

    // Odczytujemy ciasteczka z pliku.
    String cookies = readAll(file);

    // Tworzymy żądanie HTTP.
    String request = makeRequest(testedAddress, host, cookies);
    char *sendline = request->word;

    // Wysyłamy stworzone żądanie.
    if (send(sockfd , sendline , strlen(sendline) , 0) < 0) {
        printf("ERROR: writing to socket\n");
        exit(1);
    }

    /* Odczytujemy odpowiedź porcjami po 1000 znaków, zapisujemy
     * w jednej strukturze String.
     */
    bzero(recvline, MAXLINE + 10);
    String response = newString();
    bool finish = false;
    while (!finish) {
        int r = recv(sockfd, recvline, MAXLINE, 0);
        if (r < 0) {
            fprintf(stderr, "ERROR: error with reading\n");
            exit(1);
        } else if (r < MAXLINE) {
            finish = true;
        }
        if (!appendCString(response, recvline)) {
            fprintf(stderr, "ERROR: bad alloc\n");
            exit(1);
        }
    }

    // Analiza odpowiedzi serwera.
    String tmp = newString();
    bool first = true;
    finish = false;
    bool notFound = false;
    bool chunked = true;
    uint64_t lengthNormal = 0;
    uint64_t lengthChunked = 0;
    for (size_t i = 0; i < response->length && !finish; i++) {

        /* String tmp będzie przechowywał ostatnią wczytaną linijkę
         * (bez znaku '\n', ze znakiem '\r' na końcu)
         * W momencie dojścia do końca linii, odczytujemy ją,
         * zapisujemy istotne dane (np. długość zasobu), jeśli to
         * konieczne, zwalniamy tmp i tworzymy go na nowo pod wczytanie
         * kolejnej linijki.
         */
        if (response->word[i] == '\n') {
            if (first) {
                /* Jeśli odpowiedź serwera jest inna niż 200, wypisujemy
                 * linjkę z odpowiedzią i kończymy program. Odpowiedź ma
                 * postać HTML/1.1 xxx, gdzie x to cyfry, dlatego szukamy ich
                 * pod indeksami 9, 10 i 11.
                 */
                if (tmp->word[9] != '2' || tmp->word[10] != '0' ||
                   tmp->word[11] != '0') {
                    printString(tmp);
                    finish = true;
                    notFound = true;
                }
                first = false;
            }

            // Wypisujemy ciasteczko jeśli napotkamy na linijkę "Set-Cookie:"
            else if (strstr(tmp->word, "Set-Cookie:") != NULL) {
                String cookie = getCookie(tmp);
                printString(cookie);
                freeString(cookie);
            }
            /* Pobieramy długosć zasobu, jeśli zasób
             * nie został wysłany w częściach.
             */
            else if (strstr(tmp->word, "Content-Length:") != NULL) {
                chunked = false;
                String num = getContentLength(tmp);
                lengthNormal = getDecimalLength(num);
                freeString(num);
            }
            /* Pobieramy długość fragmentu zasobu, jeśli został wysłany
             * w częsciach, dodajemy ją do sumy długości części.
             */
             else if (chunked && isChunkLength(tmp)) {
                 lengthChunked += getChunkLength(tmp);
             }
            freeString(tmp);
            tmp = newString();
        } else {
            append(tmp, response->word[i]);
        }
    }

    // Wypisujemy odpowiednią długość zasobu.
    if (chunked && !notFound) {
        printf("Dlugosc zasobu: %lu\n", lengthChunked);
    } else if (!notFound) {
        printf("Dlugosc zasobu: %lu\n", lengthNormal);
    }

    // Zwalniamy pamięć.
    freeaddrinfo(addrResult);
    close(sockfd);
    fclose(file);
    freeString(request);
    freeString(response);
    freeString(tmp);
    return 0;
}
