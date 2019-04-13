CC= gcc -g
LIBS = -lpthread

.PHONY:	libpalloc.so test clean


libpalloc.so:	ngx_palloc.o ngx_alloc.o
	$(CC)	-shared -fPIC -o libpalloc.so ngx_palloc.o ngx_alloc.o

ngx_palloc.o:	ngx_palloc.c
	$(CC)	-c ngx_palloc.c

ngx_alloc.o:	ngx_alloc.c
	$(CC)	-c ngx_alloc.c

test:	main.o	libpalloc.so
	$(CC)	$(LIBS) -o test main.o -L . -lpalloc

main.o:	main.c
	$(CC)	-c main.c


clean:
	-rm *.o
	-rm *.a
	-rm *.so
	-rm test
