.PHONY: all clean run

all: main run

main: bin/main.c src/*.c src/graphics/*.c
	gcc bin/main.c src/*.c src/graphics/*.c -lm -o bin/main -I .

run: bin/main
	./bin/main

clean:
	rm ./bin/main
