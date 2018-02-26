.PHONY: all clean run

all: main run

main: main.c src/*.c src/graphics/*.c
	gcc main.c src/*.c src/graphics/*.c -lm -o main -I .

run: main
	./main

clean:
	rm ./main
