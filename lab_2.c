#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_NUM_THREADS 2

int DimensionsToLength(int xSize, int ySize)
{  return xSize*ySize; }

struct ThreadArgs
{
  int xStart;
  int yStart;
  int iterations;
  int *matrix;
  int matrixSize;
};

struct ThreadArgs threadArgsArray[MAX_NUM_THREADS];

void *DoSwaps(void *threadArgs)
{
  struct ThreadArgs *args;
  args = (struct ThreadArgs *) threadArgs;
  int x = args->xStart;
  int y = args->yStart;
  int temp;
  for (size_t i = 0; i < args->iterations; i++)
  {
    temp = args->matrix[x + y*args->matrixSize];
    args->matrix[x + y*args->matrixSize] = args->matrix[y + x*args->matrixSize];
    args->matrix[y + x*args->matrixSize] = temp;
    y++;
    if (y >= x)
    {
      y = 0;
      x++;
    }
  }
  pthread_exit(NULL);
}

void PrintMatrix(int *arr, int xSize, int ySize)
{
  int length = DimensionsToLength(xSize, ySize);
  for (size_t i = 0; i < length; i++)
  {
    printf("%d\t", arr[i]);
    if ((i+1) % xSize == 0)
      printf("\n");
  }
  printf("\n");
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
  int dimension = 8192;
  int swapLength = (dimension*(dimension - 1)) / 2;
  int iterationsPerThread = swapLength / MAX_NUM_THREADS;

  int *testArr = malloc(DimensionsToLength(dimension, dimension)*sizeof(int));
  pthread_t threads[MAX_NUM_THREADS];
  SetNumber(testArr, dimension, dimension);
  // PrintMatrix(testArr, dimension, dimension);
  double rawPos;
  int extraWorkThreads = swapLength % MAX_NUM_THREADS;
  // int xReal = 0;
  // int yReal = -1;
  int x;
  int threadNo = 0;
  int thread;

  clock_t time1 = clock();
  for (size_t i = 0; i < swapLength; i += iterationsPerThread)
  {
    rawPos = 0.5 + sqrt(0.25 + 2*i);
    x = floor(rawPos);
    threadArgsArray[threadNo].xStart = x;
    threadArgsArray[threadNo].yStart = trunc((rawPos - x) * (x + 1));
    threadArgsArray[threadNo].iterations = iterationsPerThread;
    threadArgsArray[threadNo].matrix = testArr;
    threadArgsArray[threadNo].matrixSize = dimension;

    if (threadNo < extraWorkThreads)
    {
      threadArgsArray[threadNo].iterations++;
      i++;
    }

    thread = pthread_create(&threads[threadNo], NULL, DoSwaps, (void *)&threadArgsArray[threadNo]);
    if (thread)
    {
        printf("ERROR; return code from pthread_create() is %d\n", thread);
        exit(-1);
    }
    // DoSwaps((void *) &threadArgsArray[threadNo]);

    threadNo++;
    // yReal++;
    // if (yReal >= xReal)
    // {
    //   yReal = 0;
    //   xReal++;
    // }
    // if (yReal != y || xReal != x)
    // {
    //   printf("Error:\tReal(%d,%d)\tAssumed(%d:%d)\tRaw: %f\n", xReal, yReal, x, y, rawPos);
    // }
    // if (y == x-1)
    //   printf("(%d,%d)\n", x, y);
    // else
    //   printf("(%d,%d) ", x, y);
  }
  clock_t time2 = clock();
  printf("Time: %ld\n", (double)(time2 - time1));
  // struct ThreadArgs testArgs;
  // testArgs.xStart = 0;
  // testArgs.yStart = 0;
  // testArgs.iterations = swapLength;
  // testArgs.matrix = testArr;
  // testArgs.matrixSize = dimension;

  // DoSwaps(&testArgs);
  // PrintMatrix(testArr, dimension, dimension);
  pthread_exit(NULL);
  free(testArr);

  return 0;
}
