/* Region struct: */
/*     *start -- pointer to begin of region */
/*     cursor -- pointer to begin of allocated memory */
/*     size   -- size of region (in bytes) */
/*     count  -- count of allocated objects */
typedef struct region {
  char *start;
  size_t cursor;
  size_t size;
  size_t count;
} Region;

Region *regionInit(size_t size);
void *regionIncrease(Region *region, size_t size);
void *regionAlloc(Region *region, size_t size);
void regionFree(Region *region);

#ifdef RB_ALLOC_IMPLEMENTATION
/* Default region size (in bytes) 
   You may change this value to avoid region reallocation  */
#ifndef REGION_SIZE
#define REGION_SIZE 2048
#endif

/* For development purposes */
#define UNIMPLEMENTED                                                          \
  do {                                                                         \
    fprintf(stderr, "%s() is not implemented yet\n", __func__);                \
    exit(1);                                                                   \
  } while (0)


/* Initialization function */
/* IN: */
/*     size -- memory size to allocation (in bytes) */
/* OUT: */
/*     Region* -- pointer to Region object */
/* */
/* NOTE: All memory initializated by 0 */
Region *regionInit(size_t size) {
  Region *region = malloc(sizeof(Region));

  region->start = malloc(sizeof(char) * size);
  region->cursor = 0;
  region->count = 0;
  region->size = size;

  memset(region->start, 0, size * sizeof(char));

  return region;
}

/* This function increase region size */
/* IN: */
/*     *region -- pointer to Region object */
/*     size    -- needed size to alloc  */
/* OUT: */
/*     *Region -- pointer to reallocated Region */
/* */
/* NOTE: It is not needed to increase region size by yourself */
/*       This function called by `regionAlloc` */
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

/* Allocation function */
/* IN: */
/*     *region -- pointer to Region object */
/*     size    -- memory size to allocation (in bytes) */
/* OUT: */
/*     (void*) -- pointer to allocated memory */
/* */
void *regionAlloc(Region *region, size_t size) {
  if (region->cursor + size >= region->size) {
    return regionIncrease(region, size);
  }

  region->cursor += size;
  region->count++;
  return (void *)(region->start + region->cursor - size);
}

/* This free allocated memory */
/* IN: */
/*     *region -- pointer to Region object */
void regionFree(Region *region) {
  free(region->start);
  region->start = NULL;
  region->cursor = 0;
  region->size = REGION_SIZE;
  region->count = 0;
}

/* Dumping function */
/* Prints info about Region object */
/* IN: */
/*     *region -- Region object */
void regionDump(Region *region) {
  printf("  Region dump:\n");
  printf("    cursor: %u\n", (unsigned) region->cursor);
  printf("    size:   %u\n", (unsigned) region->size);
  printf("    count:  %u\n", (unsigned) region->count);
  printf("    start:  %p\n", (void *)region->start);
}
#endif
