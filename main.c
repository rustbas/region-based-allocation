#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RB_ALLOC_IMPLEMENTATION
#include "rb_alloc.h"



int main() {

  Region *region = regionInit(REGION_SIZE);

  size_t iter_count = 15;
  for (size_t i=0; i<iter_count; i++) {
    int* tmp = regionAlloc(region, 500);
    tmp[0] = 1;
    regionDump(region);
  }

  regionDump(region);
  regionFree(region);

  return 0;
}
