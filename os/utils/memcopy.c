#include "memcopy.h"
void memcopy(unsigned char *source, unsigned char *destination,
             int total_bytes) {
    int i;
    for (i = 0; i < total_bytes; i++) {
        *(destination + i) = *(source + i);
    }
}