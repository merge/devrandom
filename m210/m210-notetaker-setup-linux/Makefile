m210drivers: m210drivers.o
	gcc -g -o m210drivers m210drivers.o -lusb-1.0

m210drivers.o: m210drivers.c m210drivers.h
	gcc -g -o m210drivers.o -c m210drivers.c

all: m210drivers

clean:
	rm -f *.o

mrproper: clean
	rm -f m210drivers raw.note
