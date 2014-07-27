alp: main.o standardio.o environment.o process.o
	gcc $(CFLAGS) -o alp main.o standardio.o environment.o process.o

main.o: main.c
	gcc $(CFLAGS) -c main.c

standardio.o: standardio.c
	gcc $(CFLAGS) -c standardio.c

environment.o: environment.c
	gcc $(CFLAGS) -c environment.c

process.o: process.c
	gcc $(CFLAGS) -c process.c

clean:
	rm -f *.o alp
