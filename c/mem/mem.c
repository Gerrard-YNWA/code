#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define random(x, t) (rand()%x + t)
#define MEMORY_BYTES 1024*1024*1024
#define BUCKETS 5

int main(){
    char* buf[BUCKETS];
    int seconds;
    srand((int)time(0));
    int bytes;
    while(1) {
        for(int i=0; i<BUCKETS; i++){
            bytes=random(MEMORY_BYTES*sizeof(char)/2, MEMORY_BYTES*sizeof(char)/2);
            printf("malloc %d bytes.\n", bytes);
	    buf[i] = (char*) malloc(bytes);
            if(!buf[i]) {
                printf("out of memory. \n");
                exit(1);
            }
            memset(buf[i], 'A', bytes);
        }
        seconds = random(240, 60);
        printf("sleep %d s before free.\n", seconds);
        sleep(seconds);
        for(int i=0; i<BUCKETS; i++){
            free(buf[i]);
        }
        seconds = random(240, 60);
        printf("sleep %d s before malloc.\n", seconds);
        sleep(seconds);
    }
    return 0;
}
