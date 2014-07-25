alp: main.o
	gcc $(CFLAGS) -o alp main.o

main.o: main.c
	gcc $(CFLAGS) -c main.c

clean:
	rm -f *.o alp
