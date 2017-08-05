all: peer2.o peer1.o

peer1.o: peer1.c
	gcc -o peer1 peer1.c -lm -std=c99

peer2.o: peer2.c
	gcc -o peer2 peer2.c -lm -std=c99

clean:
	rm -rf peer1 peer2
