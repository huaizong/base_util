CFLAGS = -g -Wformat -Wall
LDFLAGS = -L/usr/local/libzhw/lib -lzhw -lpthread -lmemcached
BINS = zhwserver
LIBS = 
all: $(BINS)
zhwserver: zhwserver.o
	gcc -o $@ $^ $(LDFLAGS)
.PHONY: clean install all
clean:
	rm *.o $(BINS) $(LIBS)
install:
