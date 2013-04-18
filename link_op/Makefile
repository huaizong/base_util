CFLAGS = -g -Wformat -Wall -std=gnu99
LDFLAGS = 
all: cpp_test test revert_link merge_link

revert_link: revert_link.c
	gcc -o $@ $^ $(LDFLAGS)
merge_link: merge_link.c
	gcc -o $@ $^ $(LDFLAGS)
test: test.c
	gcc -o $@ $^ $(LDFLAGS)
cpp_test: cpp_test.cc
	g++ -o $@ $^ $(LDFLAGS)
clean:
	rm cpp_test test revert_link merge_link
