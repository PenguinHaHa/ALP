all: alp sigaction zombie

alp: main.o standardio.o environment.o process.o thread.o
	gcc $(CFLAGS) -o alp main.o standardio.o environment.o process.o thread.o -lpthread

main.o: main.c
	gcc $(CFLAGS) -c main.c

standardio.o: standardio.c
	gcc $(CFLAGS) -c standardio.c

environment.o: environment.c
	gcc $(CFLAGS) -c environment.c

process.o: process.c
	gcc $(CFLAGS) -c process.c

thread.o: thread.c
	gcc $(CFLAGS) -c thread.c

sigaction: sigaction.o
	gcc $(CFLAGS) -o sigaction sigaction.o

sigaction.o: sigaction.c
	gcc $(CFLAGS) -c sigaction.c

zombie: zombieprocess.o
	gcc $(CFLAGS) -o zombie zombieprocess.o

zombieprocess.o: zombieprocess.c
	gcc $(CFLAGS) -c zombieprocess.c

clean:
	rm -f *.o alp sigaction zombie

