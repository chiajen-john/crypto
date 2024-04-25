CC = g++
CFLAGS = -Wall -g -Werror

crypto: main.o
	$(CC) $(CCFLAGS) -o crypto main.o -std=gnu++0x

main.o: main.cpp rsa.h type.h
	$(CC) $(CCFLAGS) -c main.cpp -std=gnu++0x

check:
	./crypto

clean:
	rm -f *.o
	rm crypto
	