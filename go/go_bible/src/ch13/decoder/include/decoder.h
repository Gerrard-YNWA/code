#include<stdbool.h>
#include<stddef.h>
typedef struct decoder{
    void* instance;
    char* data;
    size_t len;
    bool ret; 
}decoder_t;

decoder_t* new_decoder(int targetrate);

int delete_decoder(decoder_t* decoder);

void decode(decoder_t* decoder, const char* opcode, const char* data, int size);
