all: cpp_test test
test: test.c
	gcc -o test test.c
cpp_test: cpp_test.cc
	g++ -o cpp_test cpp_test.cc
clean:
	rm cpp_test test
