CFLAGS = -g -Wformat -Wall -std=gnu99
LDFLAGS = 
all: select_test oob_srv_test oob_cli_test

select_test: select_test.c
	gcc -o $@ $^ $(LDFLAGS)
oob_srv_test: oob_srv_test.c
	gcc -o $@ $^ $(LDFLAGS)
oob_cli_test: oob_cli_test.c
	gcc -o $@ $^ $(LDFLAGS)
clean:
	rm select_test oob_srv_test oob_cli_test
