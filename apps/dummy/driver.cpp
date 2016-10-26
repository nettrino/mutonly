#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int compare(const void *a, const void *b)
{
  if (!a || !b) return 0;
  return ( *(uint8_t *)a - *(uint8_t *)b);
}

extern "C"
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
  uint8_t *tmp = (uint8_t *) malloc(Size);
  if (tmp == NULL) {
    printf("malloc failed\n");
    return 0;
  }

  memcpy(tmp, Data, Size);
  qsort(tmp, Size / sizeof(uint8_t), sizeof(uint8_t), compare);

  free(tmp);
  return 0;
}
