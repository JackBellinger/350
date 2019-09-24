task = task1

all: $(task)

$(task): $(task).o
	gcc -o $(task) $(task).o

$(task6).o: $(task).c
	gcc -std=c99 -c $(task).c 

clean: 
	rm -rf *.o main
