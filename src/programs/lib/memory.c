#define HEAP_SIZE 4096

volatile unsigned char HEAP[HEAP_SIZE]; __attribute__((section(".os_data")));
volatile unsigned short heap_ptr = 0; __attribute__((section(".os_data")));

struct heap_segment
{
    void* address; // start address
    unsigned short size; // segment size
};

volatile struct heap_segment heap_segments[HEAP_SIZE]; __attribute__((section(".os_data")));
volatile unsigned short heap_segments_ptr = 0; __attribute__((section(".os_data")));

void* memory_alloc(unsigned short size){

    for (unsigned short ptr = 0; ptr < heap_ptr; ptr++){

    }

    // if adress != heap_segment.address or adress > (heap_segment.address+heap_segment.size)

    void* address = 1;
    return address;
}

void memory_free(void* address){

}
