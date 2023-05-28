CC = gcc
CFLAGS = -Wall -std=c99 -O3

default: wrdmttns

wrdmttns: main.o file.o array.o graph.o heap.o dijkstra.o
	$(CC) $(CFLAGS) -o wrdmttns main.o file.o array.o graph.o heap.o dijkstra.o

main.o: main.c file.h array.h graph.h heap.h
	$(CC) $(CFLAGS) -c main.c

file.o: file.c file.h
	$(CC) $(CFLAGS) -c file.c

array.o: array.c array.h
	$(CC) $(CFLAGS) -c array.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c 

heap.o: heap.c heap.h
	$(CC) $(CFLAGS) -c heap.c

dijkstra.o:  dijkstra.c dijkstra.h
	$(CC) $(CFLAGS) -c dijkstra.c

clean:
	rm -rf *.o $(wrdmttns) *~