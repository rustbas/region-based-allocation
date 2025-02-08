#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RB_ALLOC_IMPLEMENTATION
#include "rb_alloc.h"



int main() {

  // Region initialization
  Region *region = regionInit(REGION_SIZE);

  // Printing info about region
  printf("Region dump after init:\n");
  regionDump(region);
  printf("\n");

  // Allocation matrix on region
  const size_t ROWS = 3;
  const size_t COLS = 4;

  double** matrix = regionAlloc(region, sizeof(double*)*ROWS);
  for (size_t i = 0; i < ROWS; i++)
    matrix[i] = regionAlloc(region, sizeof(double)*COLS);

  for (size_t i = 0; i < ROWS; i++)
    for (size_t j = 0; j < COLS; j++)
      matrix[i][j] = rand() / (double) RAND_MAX;

  printf("matrix = \n");
  for (size_t i = 0; i < ROWS; i++) {
    for (size_t j = 0; j < COLS; j++)
      printf("%5.3f\t", matrix[i][j]);
    printf("\n");
  }
  printf("\n");

  printf("Region dump after matrix allocation:\n");
  regionDump(region);
  printf("\n");

  regionFree(region);
  printf("Region dump after freeing region:\n");
  regionDump(region);

  return 0;
}
