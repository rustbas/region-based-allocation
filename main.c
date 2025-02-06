#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGION_SIZE 64000

typedef struct {
  int *start;
  size_t cursor;
} Region;

void regionInit(Region *region, size_t size){
  region->start = malloc(sizeof(int)*size);
  region->cursor = 0;

  memset(region->start, 0, size*sizeof(int));
}

void* regionAlloc(Region *region, size_t size) {
  region->cursor += size;
  return (void*)(region->start + region->cursor - size);
}

void regionFree(Region *region) {
  free(region->start);
  region->cursor = 0;
}

void regionDump(Region *region) {
  printf("Region dump:\n");
  printf("    cursor: %zu\n", region->cursor);
  printf("     start: %p\n", (void*) region->start);
}

int main() {

  Region region;
  regionInit(&region, REGION_SIZE);
  
  size_t test_size = 10;
  int *test = (int*)regionAlloc(&region, test_size);
  
  for (size_t i=0; i<test_size; i++) {
    test[i] = i*i*i;
    printf("%d\n", test[i]);
  }

  regionDump(&region);

  printf("hello, world!\n");

  regionFree(&region);

  return 0;
}
