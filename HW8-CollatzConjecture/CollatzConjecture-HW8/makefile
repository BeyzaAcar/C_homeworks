all: clean compile run 

clean:
	@rm -f test

compile: main.c util.c util.h
	@gcc -o test main.c util.c util.h

run:
	@./test
