.PHONY: all clean run

all: main run

main: *.c
	gcc *.c -o main -I .

run: main
	./main

clean:
	rm ./main
