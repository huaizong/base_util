CFLAGS = -g -Wformat -Wall
LDFLAGS = -lpthread
BINS = test_zhw_worker_pool
LIBS = libzhw.a
all: $(LIBS) $(BINS)
libzhw.a: zhw_worker_pool.o zhw_log.o zhw_cache.o
	ar cru $@ $^
test_zhw_worker_pool: test_zhw_worker_pool.o
	gcc -o $@ $^ $(LDFLAGS) libzhw.a
clean:
	rm *.o $(BINS) $(LIBS)







