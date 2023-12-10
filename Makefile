build:
	gcc -Wall -std=c99 ./src/*.c -o bitminton

run:
	./bitminton

clean:
	rm bitminton
