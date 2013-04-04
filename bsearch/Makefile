CFLAGS = -g -Wformat -Wall
LDFLAGS = 
BINS = binary_search
.PHONY: clean
default: $(BINS)
all: $(BINS)
test_zhw_worker_pool: binary_search.o
	gcc -o $@ $^ $(LDFLAGS)
clean:
	rm *.o $(BINS)







