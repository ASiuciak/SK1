CFLAGS = -Wall -Wextra -g -O2


testhttp_raw: main.o stringBuilder.o readCookies.o readResponse.o makeRequest.o
			gcc -o testhttp_raw main.o stringBuilder.o readCookies.o readResponse.o makeRequest.o

main.o: main.c
		gcc -c $(CFLAGS) main.c -o main.o

stringBuilder.o: stringBuilder.c
		gcc -c $(CFLAGS) stringBuilder.c -o stringBuilder.o

readCookies.o: readCookies.c
		gcc -c $(CFLAGS) readCookies.c -o readCookies.o

readResponse.o: readResponse.c
		gcc -c $(CFLAGS) readResponse.c -o readResponse.o

makeRequest.o: makeRequest.c
		gcc -c $(CFLAGS) makeRequest.c -o makeRequest.o

clean:
		rm -f *.o testhttp_raw
