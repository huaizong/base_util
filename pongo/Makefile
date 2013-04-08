CFLAGS = -g -Wformat -Wall
LDFLAGS = 
BINS = max_ary_sum find_min_k
.PHONY: clean
default: $(BINS)
all: $(BINS)
max_ary_sum: max_ary_sum.o
	gcc -o $@ $^ $(LDFLAGS)
find_min_k: find_min_k.o
	gcc -o $@ $^ $(LDFLAGS)
clean:
	rm *.o $(BINS)







