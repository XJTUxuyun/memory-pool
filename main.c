#include <stdio.h>
#include "ngx_palloc.h"
#include <sys/time.h>

uint64_t usTime()
{
    struct timeval tv;
    uint64_t usec;
    
    gettimeofday(&tv, NULL);
    
    usec = ((uint64_t)tv.tv_sec)*1000000LL;
    usec += tv.tv_usec;
    
    return usec;
}

void dump_pool(ngx_pool_t *pool){
	while(pool){
		printf("pool 0x%p\n", pool);
		pool = pool->d.next;
	}
}

int main(){
	ngx_pool_t *pool;
	pool = ngx_create_pool(10240);

	dump_pool(pool);

	void *p = ngx_palloc(pool, 512);
	ngx_palloc(pool, 512);
	printf("p = 0x%p\n", p);
	dump_pool(pool);

	printf("___________________bench_________________\n");
    
    
    
    uint64_t us_begin;
    uint64_t us_end;
    size_t size[] = { 30, 120, 256, 500, 1000, 2000, 3000, 5000};
    
    printf("size\tncx\tmalloc\tpct\n");
    
    int i, j;
    uint64_t t1, t2;
    for (j = 0; j < sizeof(size)/sizeof(size_t); j++)
    {
        size_t s = size[j];
        printf("%d\t", s);
        
        //test for ncx_pool
        us_begin  = usTime();
        for(i = 0; i < 10000; i++)
        {
            p = ngx_palloc(pool, s);
            
            ngx_pfree(pool, p);
        }
        us_end  = usTime();
        
        t1 = (us_end - us_begin);
        printf("%llu \t", t1/1000);
        
        // test for malloc
        us_begin  = usTime();
        for(i = 0; i < 10000; i++)
        {
            p = (char*)malloc(s);
            
            free(p);
        }
        us_end  = usTime();
        
        t2 = (us_end - us_begin);
        printf("%llu\t", t2/1000);
        
        printf("%.2f\n", (double)t1 / (double)t2);
    }
    


	return 0;
}
