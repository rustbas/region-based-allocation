#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RB_ALLOC_IMPLEMENTATION
#include "rb_alloc.h"



int main() {

  Region *region = regionInit(REGION_SIZE);


  regionDump(region);
  regionFree(region);

  return 0;
}
