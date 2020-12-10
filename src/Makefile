CC=gcc
CFLAGS=-Wall -Ofast --std=c99 -g
LDFLAGS=-lSDL2

eratosthene.o: eratosthene.c eratosthene.h
	$(CC) $(CFLAGS) -c eratosthene.c -o $@

ulam.o: ulam.c ulam.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o test

test_eratosthene: CFLAGS += -DDEBUG
test_eratosthene: eratosthene.o
	$(CC) $(CFLAGS) $^ test_eratosthene.c $(LDFLAGS) -o $@

test: CFLAGS += -DDEBUG
test: eratosthene.o ulam.o
	$(CC) $(CFLAGS) $^ test_ulam.c $(LDFLAGS) -o $@

ulamsdl: eratosthene.o ulam.o
	$(CC) $(CFLAGS) $^ test_ulam.c $(LDFLAGS) -o $@
