CFLAGS = -g -Wformat -Wall
LDFLAGS = 
BINS = binary_search
.PHONY: clean
default: $(BINS)
all: $(BINS)
binary_search: main_test.o binary_search.o quick_sort.o heap_sort.o bubble_sort.o
	gcc -o $@ $^ $(LDFLAGS)
clean:
	rm *.o $(BINS)







