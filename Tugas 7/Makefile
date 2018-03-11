.PHONY: all clean run

all: main run

bin:
	mkdir bin

main: bin main.c src/*.c src/graphics/*.c
	gcc main.c src/*.c src/graphics/*.c -lm -o bin/main -I .

run: bin/main
	./bin/main

clean:
	rm ./bin/main
