SRCS = test.c

default:  libapi_a.a libapi_b.so test_a test_b

libapi_a.a: $(OBJS)
	cd liba; make

libapi_b.so: $(OBJS)
	cd libb; make

test_a: test.c liba/libapi_a.a libb/libapi_b.so
	gcc -o test_a test.c ./liba/libapi_a.a -L./libb/ -lapi_b
test_b: test.c liba/libapi_a.a libb/libapi_b.so
	gcc -o test_b test.c -L./libb/ -lapi_b  ./liba/libapi_a.a 

clean:
	$(RM) $(OBJS)
	$(RM) test_a test_b *.so *.a *.so.0
	cd liba; make clean
	cd libb; make clean
