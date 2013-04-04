CFLAGS = -g -Wformat -Wall
LDFLAGS = 
BINS = heap_sort
.PHONY: clean
default: $(BINS)
all: $(BINS)
test_zhw_worker_pool: heap_sort.o
	gcc -o $@ $^ $(LDFLAGS)
clean:
	rm *.o $(BINS)







