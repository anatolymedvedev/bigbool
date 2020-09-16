all: clean test_unit test_xor build

build: main.c bool.o
	@gcc -g -Wall -o main ./main.c ./bool.o

bool.o: bigbool.c bigbool.h
	@gcc -g -c -o bool.o ./bigbool.c

test_unit: test.c bool.o
	@gcc -g -o test_unit ./test.c ./bool.o
	@./test_unit

test_xor: xor.c bool.o
	@gcc -g -o test_xor ./xor.c ./bool.o
	@./test_xor

clean:
	@rm -f ./bool.o