CFLAGS = -g -Wformat -Wall
LDFLAGS = -lpthread -lmemcached
BINS = sample_zhw_worker_pool sample_zhw_word_split sample_zhw_tcp
LIBS = libzhw.a
all: $(LIBS) $(BINS)
libzhw.a: zhw_worker_pool.o zhw_log.o zhw_cache.o zhw_word_split.o zhw_memcache.o zhw_top_n.o zhw_tcp.o
	ar cru $@ $^
sample_zhw_word_split: sample_zhw_word_split.o
	gcc -o $@ $^ $(LDFLAGS) libzhw.a
sample_zhw_worker_pool: sample_zhw_worker_pool.o
	gcc -o $@ $^ $(LDFLAGS) libzhw.a
sample_zhw_tcp: sample_zhw_tcp.o
	gcc -o $@ $^ $(LDFLAGS) libzhw.a
.PHONY: clean install uninstall all
clean:
	rm *.o $(BINS) $(LIBS)
install:
	mkdir -p ${DESTDIR}/usr/local/lib/libzhw
	mkdir -p ${DESTDIR}/usr/local/include/libzhw
	install -m 644 zhw_log.h ${DESTDIR}/usr/local/include/libzhw
	install -m 644 zhw_cache.h ${DESTDIR}/usr/local/include/libzhw
	install -m 644 zhw_word_split.h ${DESTDIR}/usr/local/include/libzhw
	install -m 644 zhw_tcp.h ${DESTDIR}/usr/local/include/libzhw
	install -m 755 libzhw.a ${DESTDIR}/usr/local/lib/libzhw
uninstall:
	rm -rf  ${DESTDIR}/usr/local/libzhw
