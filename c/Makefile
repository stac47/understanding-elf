CFLAGS=-Wall -O0 -g

all: prog0 prog1_static prog1_dynamic

prog0: prog0.c nothing.c nothing.o libnothing.so
	gcc $(CFLAGS) -c prog0.c
	gcc $(CFLAGS) prog0.o nothing.o -o prog0.out
	gcc -o prog0_dynamic.out prog0.o -L. -lnothing

nothing.o: nothing.c
	gcc $(CFLAGS) -c nothing.c 

libnothing.so: nothing.c
	gcc $(CFLAGS) -fPIC -c nothing.c -onothing_pic.o
	gcc -shared -fuse-ld=gold -o libnothing.so nothing_pic.o

hack_nothing: hack_nothing.c libnothing.so
	gcc $(CFLAGS) -o hack_nothing.out hack_nothing.c -L. -lnothing -ldl

prog1_static: prog1.c libprinter_static nothing.o
	gcc -c $(CFLAGS) -I. -oprog1_static.o prog1.c
	gcc -oprog1_static.out prog1_static.o nothing.o -L. -Bstatic -lprinter

prog1_dynamic: prog1.c libprinter_shared libnothing.so
	gcc $(CFLAGS) -oprog1_dynamic.out prog1.c -I. -L. -lprinter -lnothing

libprinter_static: printer.o
	ar -cvq libprinter.a printer.o

libprinter_shared: printer_pic.o
	gcc -shared -Wl,-soname,libprinter.so.1 -olibprinter.so.1.0.0 printer_pic.o
	ln -fs libprinter.so.1.0.0 libprinter.so.1
	ln -fs libprinter.so.1 libprinter.so

printer_pic.o: printer.c
	gcc $(CFLAGS) -fPIC -c -o printer_pic.o printer.c

printer.o: printer.c
	gcc $(CFLAGS) -c -o printer.o printer.c

clean:
	rm *.o *.so* *.a *.out
