CFLAGS = -g -Wformat -Wall
LDFLAGS = 
BINS = test_zhw_worker_pool
.PHONY: clean
default: $(BINS)
all: $(BINS)
test_zhw_worker_pool: test_zhw_worker_pool.o zhw_worker_pool.o zhw_log.o
	gcc -o $@ $^ $(LDFLAGS)
clean:
	rm *.o $(BINS)







