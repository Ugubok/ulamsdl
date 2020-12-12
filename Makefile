CC=gcc
CFLAGS=-Wall -Ofast --std=c99
LDFLAGS=-lSDL2

ulamsdl: eratosthene.o ulam.o
	$(CC) $(CFLAGS) $^ test_ulam.c $(LDFLAGS) -o $@

debug: CFLAGS += -DDEBUG -g
debug: eratosthene.o ulam.o
	$(CC) $(CFLAGS) $^ test_ulam.c $(LDFLAGS) -o $@

eratosthene.o: eratosthene.c eratosthene.h
	$(CC) $(CFLAGS) -c $< -o $@

ulam.o: ulam.c ulam.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o test ulamsdl debug

test_eratosthene: CFLAGS += -DDEBUG
test_eratosthene: eratosthene.o
	$(CC) $(CFLAGS) $^ test_eratosthene.c $(LDFLAGS) -o $@



