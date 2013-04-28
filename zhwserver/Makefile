CFLAGS = -g -Wformat -Wall -I/usr/local/include/libzhw
LDFLAGS = -L/usr/local/lib/libzhw -lzhw -lpthread -lmemcached
BINS = zhw_server
LIBS = 
all: $(BINS)
zhw_server: zhw_server.o
	gcc -o $@ $^ $(LDFLAGS)
.PHONY: clean install all
clean:
	rm *.o $(BINS) $(LIBS)
install:
