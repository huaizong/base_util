#CFLAGS = -g -Wformat -Wall
CFLAGS = -g -Wformat -Wall -DZHW_DEBUG -DZHW_USE_EPOLL
LDFLAGS = -lpthread -lmemcached
BINS = sample_zhw_ini sample_zhw_worker_pool sample_zhw_word_split sample_zhw_tcp
LIBS = libzhw.a
DESTDIR= /usr/local
LIB_ZHW_INST_ROOT=${DESTDIR}/libzhw
LIB_ZHW_LIB_INST_DIR = ${LIB_ZHW_INST_ROOT}/lib
LIB_ZHW_HEADER_INST_DIR = ${LIB_ZHW_INST_ROOT}/include

all: $(LIBS) $(BINS)
libzhw.a: zhw_worker_pool.o zhw_log.o \
		zhw_cache.o zhw_word_split.o \
		zhw_memcache.o zhw_top_n.o \
		zhw_tcp.o zhw_ini.o \
		zhw_sys.o \
		zhw_stack.o \
		zhw_dict.o \
		zhw_algorithm.o \
		zhw_top_n.o \
		zhw_str.o \
		zhw_email.o \
		zhw_p2p.o
	ar cru $@ $^

sample_zhw_ini: sample_zhw_ini.o
	gcc -o $@ $^ $(LDFLAGS) libzhw.a
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
	mkdir -p ${LIB_ZHW_LIB_INST_DIR}
	mkdir -p ${LIB_ZHW_HEADER_INST_DIR}
	install -m 644 zhw_log.h ${LIB_ZHW_HEADER_INST_DIR}
	install -m 644 zhw_cache.h ${LIB_ZHW_HEADER_INST_DIR}
	install -m 644 zhw_word_split.h ${LIB_ZHW_HEADER_INST_DIR}
	install -m 644 zhw_tcp.h ${LIB_ZHW_HEADER_INST_DIR}
	install -m 755 libzhw.a ${LIB_ZHW_LIB_INST_DIR}

uninstall:
	rm -rf  $(LIB_ZHW_INST_ROOT)
