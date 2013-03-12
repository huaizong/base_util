all: cpp_test test revert_link
revert_link: revert_link.c
    gcc -std=gnu99 -o revert_link revert_link.c
test: test.c
	gcc -std=gnu99  -o test test.c
cpp_test: cpp_test.cc
	g++ -o cpp_test cpp_test.cc
clean:
	rm cpp_test test revert_link
