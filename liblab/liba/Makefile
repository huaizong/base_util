SRCS = api_a.c

OBJS = $(SRCS:.c=.o)

default:  libapi_a.a

libapi_a.a: $(OBJS)
	@($(AR) $(ARFLAGS) $@ $(OBJS))

clean:
	$(RM) $(OBJS)
	$(RM) *.so *.a *.so.0
