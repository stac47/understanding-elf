CFLAGS=-Wall -Og -g -march=x86-64

%.o: %.c %.h
	gcc $(CFLAGS) -fPIC -c -o $@ $<

libprinter.so: init.o hello.o goodbye.o
	gcc -shared $(CFLAGS) -fPIC -o $@ $^

all: client.out

client.out: client.c libprinter.so
	gcc $(CFLAGS) -o$@ $< -I. -L. -lprinter

clean:
	rm *.o *.so* *.a *.out
