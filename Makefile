build:
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -o bitminton

run:
	./bitminton

clean:
	rm bitminton
