#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int DimensionsToLength(int xSize, int ySize)
{  return xSize*ySize; }

void PrintMatrix(int *arr, int xSize, int ySize)
{
  int length = DimensionsToLength(xSize, ySize);
  for (size_t i = 0; i < length; i++)
  {
    printf("%d\t", arr[i]);
    if ((i+1) % xSize == 0)
      printf("\n");
  }
}

void SetNumber(int *arr, int xSize, int ySize)
{
  int length = DimensionsToLength(xSize, ySize);

  for (int i = 0; i < length; i++)
  {
    arr[i] = i+1;
  }
}

int main(int argc, char const *argv[])
{
  printf("Using A[10][10] Array:\n\n");
  int dimension = 5;
  int *testArr = malloc(DimensionsToLength(dimension, dimension)*sizeof(int));
  SetNumber(testArr, dimension, dimension);
  PrintMatrix(testArr, dimension, dimension);
  free(testArr);

  return 0;
}
