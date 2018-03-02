.PHONY: all clean run

all: main run

main: main.c src/*.c src/graphics/*.c
	gcc main.c src/*.c src/graphics/*.c -lm -o bin/main -I .

run: bin/main
	./bin/main

clean:
	rm ./bin/main
