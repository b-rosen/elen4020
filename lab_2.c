#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
  int dimension = 13;
  int *testArr = malloc(DimensionsToLength(dimension, dimension)*sizeof(int));
  SetNumber(testArr, dimension, dimension);
  // PrintMatrix(testArr, dimension, dimension);
  int swapLength = (dimension*(dimension - 1)) / 2;
  int x;
  int y;
  for (size_t i = 0; i < swapLength; i++)
  {
    float rawPos = 0.5 + sqrt(0.25 + 2*i);
    x = (int) rawPos;
    y = (rawPos - x) * (x + 1);
    if (y == x - 1)
      printf("(%d:%d)\n", x, y);
    else
      printf("(%d:%d), ", x, y);
  }
  free(testArr);

  return 0;
}
