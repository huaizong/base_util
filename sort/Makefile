CFLAGS = -g -Wformat -Wall
LDFLAGS = 
BINS = test
.PHONY: clean
default: $(BINS)
all: $(BINS)
test: main_test.o binary_search.o quick_sort.o heap_sort.o bubble_sort.o select_sort.o half_vote.o
	gcc -o $@ $^ $(LDFLAGS)
find_min_k: find_min_k.o
	gcc -o $@ $^ $(LDFLAGS)
clean:
	rm *.o $(BINS)







