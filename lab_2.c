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
  double rawPos;
  int xReal = 0;
  int yReal = -1;
  for (size_t i = 0; i < 33550336; i++)
  {
    rawPos = 0.5 + sqrt(0.25 + 2*i);
    x = floor(rawPos);
    y = trunc((rawPos - x) * (x + 1));
    yReal++;
    if (yReal >= xReal)
    {
      yReal = 0;
      xReal++;
    }
    if (yReal != y || xReal != x)
    {
      printf("Error:\tReal(%d,%d)\tAssumed(%d:%d)\tRaw: %f\n", xReal, yReal, x, y, rawPos);
    }
  }
  free(testArr);

  return 0;
}
