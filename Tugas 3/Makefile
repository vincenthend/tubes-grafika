.PHONY: all clean run

all: main run

main: main.c drawer.c graphics.c framebuffer.c printer.c rasterizer.c color.c
	gcc main.c drawer.c graphics.c framebuffer.c printer.c rasterizer.c color.c -lm -o main -I .

run: main
	./main

clean:
	rm ./main
