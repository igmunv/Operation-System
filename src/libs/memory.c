#include "memory.h"

int memcpy(void* dst, void* src, int size){

    for (int i = 0; i < size; i++){

        char* src_byte = src+i;
        char* dst_byte = dst+i;
        *dst_byte = *src_byte;


    }

}
