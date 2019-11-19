all: pipe1 pipe3 pipe4 pipeFifo twoPipesParent twoPipesChild pipeFifo

pipe1: pipe1.c
	gcc -o pipe1 pipe1.c

pipe3: pipe3.c
	gcc -o pipe3 pipe3.c

pipe4: pipe4.c
	gcc -o pipe4 pipe4.c

twoPipesParent: twoPipesParent.c
	gcc -o twoPipesParent twoPipesParent.c

twoPipesChild: twoPipesChild.c
	gcc -o twoPipesChild twoPipesChild.c

pipeFifo: pipeFifo.c
	gcc -o pipeFifo pipeFifo.c

clean:
	rm -rf *.o
