#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGION_SIZE 2048
#define RAND (rand() / (double) RAND_MAX)

#define UNIMPLEMENTED \
  do { \
    fprintf(stderr, "%s() is not implemented yet\n", __func__); \
    exit(1); \
  } while(0) 

typedef struct {
  int8_t *start;
  size_t cursor;
  size_t size;
  size_t count;
} Region;

void regionInit(Region *region, size_t size){
  region->start = malloc(sizeof(int8_t)*size);
  region->cursor = 0;
  region->count = 0;
  region->size = size;

  memset(region->start, 0, size*sizeof(int8_t));
}

void* regionIncrease(Region *region, size_t size) {
  size_t n = 2;
  while (region->size + size >= region->size*n) n <<= 1;

  region->size = region->size*n;
  region->start = realloc(region->start, region->size);
  region->cursor += size;
  region->count++;

  return (void*)(region->start + region->cursor - size);
}

void* regionAlloc(Region *region, size_t size) {
  if (region->cursor + size >= region->size) {
    return regionIncrease(region, size);
  }

  region->cursor += size;
  region->count++;
  return (void*)(region->start + region->cursor - size);
}

void regionFree(Region *region) {
  free(region->start);
  region->cursor = 0;
}

void regionDump(Region *region) {
  printf("Region dump:\n");
  printf("    cursor: %zu\n", region->cursor);
  printf("    size:   %zu\n", region->size);
  printf("    count:  %zu\n", region->count);
  printf("    start:  %p\n", (void*) region->start);
}

int main() {

  Region *region = malloc(sizeof(Region));
  regionInit(region, REGION_SIZE);
  

  regionDump(region);
  regionFree(region);

  return 0;
}
