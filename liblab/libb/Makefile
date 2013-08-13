SRCS = api_b.c

OBJS = $(SRCS:.c=.o)

default:  libapi_b.so

libapi_b.so: $(OBJS)
	gcc -fPIC -shared -o libapi_b.so api_b.c

clean:
	$(RM) $(OBJS)
	$(RM) *.so *.a *.so.0
