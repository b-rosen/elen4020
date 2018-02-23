#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int DimensionsToLength(int *dimensionArr, int dimension)
{
  int length = 1;
  for (int i = 0; i < dimension; i++)
  {
    length *= dimensionArr[i];
  }
  return length;
}

void SetZero(int *arr, int *dimensionArr, int dimension)
{
  int length = DimensionsToLength(dimensionArr, dimension);
  for (int i = 0; i < length; i++)
  {
    arr[i] = 0;
  }
}

void SetOne(int *arr, int *dimensionArr, int dimension)
{
  int length = DimensionsToLength(dimensionArr, dimension);
  int increment = length * 0.1;
  for (int i = 0; i < length; i += increment)
  {
    arr[i] = 1;
  }
}

void RandPos(int *arr, int *dimensionArr, int dimension)
{
  int length = DimensionsToLength(dimensionArr, dimension);
  int rep = length * 0.05;
  srand(time(NULL));

  int arrPos[dimension];
  for (int i = 0; i < rep; i++)
  {
    int position = rand() % length;
    printf("The Selected Value is: %d\nAt Position: ", arr[position]);

    for (int j = dimension - 1; j >= 0; j--)
    {
      arrPos[j] = position % dimensionArr[j];
      position /= dimensionArr[j];
    }
    for (int j = 0; j < dimension; j++) { printf("[%d]", arrPos[j]); }
    printf("\n\n");
  }
}

int main(int argc, char const *argv[])
{
  printf("Using A[100][100] Array:\n\n");
  int dimension = 2;
  int dimensionArr1[2] = {100, 100};
  int *testArr = malloc(DimensionsToLength(dimensionArr1, dimension)*sizeof(int));
  SetZero(testArr, dimensionArr1, dimension);
  SetOne(testArr, dimensionArr1, dimension);
  RandPos(testArr, dimensionArr1, dimension);
  free(testArr);

  printf("Using A[100][100][100] Array:\n\n");
  dimension = 3;
  int dimensionArr2[3] = {100, 100, 100};
  testArr = malloc(DimensionsToLength(dimensionArr2, dimension)*sizeof(int));
  SetZero(testArr, dimensionArr2, dimension);
  SetOne(testArr, dimensionArr2, dimension);
  RandPos(testArr, dimensionArr2, dimension);
  free(testArr);

  printf("Using A[50][50][50][50] Array:\n\n");
  dimension = 4;
  int dimensionArr3[4] = {50, 50, 50, 50};
  testArr = malloc(DimensionsToLength(dimensionArr3, dimension)*sizeof(int));
  SetZero(testArr, dimensionArr3, dimension);
  SetOne(testArr, dimensionArr3, dimension);
  RandPos(testArr, dimensionArr3, dimension);
  free(testArr);

  printf("Using A[20][20][20][20][20] Array:\n\n");
  dimension = 5;
  int dimensionArr4[5] = {20, 20, 20, 20, 20};
  testArr = malloc(DimensionsToLength(dimensionArr4, dimension)*sizeof(int));
  SetZero(testArr, dimensionArr4, dimension);
  SetOne(testArr, dimensionArr4, dimension);
  RandPos(testArr, dimensionArr4, dimension);
  free(testArr);

  return 0;
}
