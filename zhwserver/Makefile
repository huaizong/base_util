CFLAGS = -g -Wformat -Wall -I/usr/local/include/libzhw
LDFLAGS = -L/usr/local/lib/libzhw -lzhw -lpthread -lmemcached
BINS = zhw_server
LIBS = 
all: $(BINS)
zhw_server: zhw_server.o zhw_smtp.o
	gcc -o $@ $^ $(LDFLAGS)
.PHONY: clean install all
clean:
	rm *.o $(BINS) $(LIBS)
install:
	mkdir -p ${DESTDIR}/usr/local/zhw
	mkdir -p ${DESTDIR}/usr/local/etc/zhw
	mkdir -p ${DESTDIR}/var/run/zhw
	cp zhw_server ${DESTDIR}/usr/local/zhw
	install -s -m 0755 -o root -g wheel zhw_server /usr/local/zhw/zhw_server
	install -m 755 scripts/zhw_server.sysv /etc/init.d/zhw_server
uninstall:
	rm -rf ${DESTDIR}/usr/local/zhw
