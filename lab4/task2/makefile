task = task2

all: main

main: tmp/main.o
	gcc -std=c99 -o main tmp/main.o
tmp/main.o: $(task).c tmp
	gcc -std=c99 -c -o tmp/main.o $(task).c
clean:
	rm -rf main tmp
tmp:
	mkdir -p tmp 
