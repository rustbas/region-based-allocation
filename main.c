#include <stdio.h>

#define REGION_SIZE 64000

typedef struct {
  int start[REGION_SIZE];
  size_t cursor;
} Region;

int* regionAlloc(Region *region, size_t size) {
  region->cursor += size;
  return region->start - size;
}

int main() {

  Region region = {0};

  size_t test_size = 10;
  int *test = regionAlloc(&region, test_size);
  test[1] = 10;
  test[2] = 10;

  for (size_t i=0; i<test_size; i++) {
    test[i] = 0;
  }
  
  for (size_t i=0; i<test_size; i++) {
    printf("%d\n", test[i]);
  }

  printf("hello, world!\n");

  return 0;
}
