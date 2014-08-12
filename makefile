all: alp sigaction zombie sharedmemory pipe socket_server socket_client

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

sharedmemory: sharedmemory.o
	gcc $(CFLAGS) -o sharedmemory sharedmemory.o

sharedmemory.o: sharedmemory.c
	gcc $(CFLAGS) -c sharedmemory.c

pipe: pipe.o
	gcc $(CFLAGS) -o pipe pipe.o

pipe.o: pipe.c
	gcc $(CFLAGS) -c pipe.c

socket_client: socket_client.o
	gcc $(CFLAGS) -o socket_client socket_client.o

socket_client.o: socket_client.c
	gcc $(CFLAGS) -c socket_client.c

socket_server: socket_server.o
	gcc $(CFLAGS) -o socket_server socket_server.o

socket_server.o: socket_server.c
	gcc $(CFLAGS) -c socket_server.c

clean:
	rm -f *.o alp sigaction zombie sharedmemory pipe socket_client socket_server

