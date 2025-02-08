typedef struct region Region;
Region *regionInit(size_t size);
void *regionIncrease(Region *region, size_t size);
void *regionAlloc(Region *region, size_t size);
void regionFree(Region *region);

#ifdef RB_ALLOC_IMPLEMENTATION
#ifndef REGION_SIZE
#define REGION_SIZE 2048
#endif

#define UNIMPLEMENTED                                                          \
  do {                                                                         \
    fprintf(stderr, "%s() is not implemented yet\n", __func__);                \
    exit(1);                                                                   \
  } while (0)

typedef struct region {
  int8_t *start;
  size_t cursor;
  size_t size;
  size_t count;
} Region;

Region *regionInit(size_t size) {
  Region *region = malloc(sizeof(Region));

  region->start = malloc(sizeof(int8_t) * size);
  region->cursor = 0;
  region->count = 0;
  region->size = size;

  memset(region->start, 0, size * sizeof(int8_t));

  return region;
}

void *regionIncrease(Region *region, size_t size) {
  size_t n = 2;
  while (region->size + size >= region->size * n)
    n <<= 1;

  region->size = region->size * n;
  region->start = realloc(region->start, region->size);
  region->cursor += size;
  region->count++;

  return (void *)(region->start + region->cursor - size);
}

void *regionAlloc(Region *region, size_t size) {
  if (region->cursor + size >= region->size) {
    return regionIncrease(region, size);
  }

  region->cursor += size;
  region->count++;
  return (void *)(region->start + region->cursor - size);
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
  printf("    start:  %p\n", (void *)region->start);
}
#endif
