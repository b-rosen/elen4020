#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_NUM_THREADS 16

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
  SetNumber(testArr, dimension, dimension);
  // PrintMatrix(testArr, dimension, dimension);
  int extraWorkThreads = swapLength % MAX_NUM_THREADS;
  // int xReal = 0;
  // int yReal = -1;
  int x;
  int y;
  int threadID;
  double rawPos;
  int swapIteration;
  int _iterationsPerThread;
  int temp;
  size_t i;

  struct timespec time1, time2;

  clock_gettime(CLOCK_REALTIME, &time1);
  #pragma omp parallel shared(extraWorkThreads, testArr, dimension, iterationsPerThread) private(x, y, threadID, rawPos, swapIteration, _iterationsPerThread, temp, i) num_threads(MAX_NUM_THREADS)
  {
    threadID = omp_get_thread_num();
    _iterationsPerThread = iterationsPerThread;
    if (threadID < extraWorkThreads)
    {
      swapIteration = threadID + threadID*iterationsPerThread;
      _iterationsPerThread++;
    }
    else if (threadID == 0)
    {
      swapIteration = threadID + threadID*iterationsPerThread;
    }
    else
      swapIteration = extraWorkThreads + threadID*iterationsPerThread;

    rawPos = 0.5 + sqrt(0.25 + 2*swapIteration);
    x = floor(rawPos);
    y = trunc((rawPos - x) * (x + 1));
    // printf("Thread %d: (%d, %d)\n", threadID, x, y);
    for (i = 0; i < _iterationsPerThread; i++)
    {
      temp = testArr[x + y*dimension];
      testArr[x + y*dimension] = testArr[y + x*dimension];
      testArr[y + x*dimension] = temp;
      y++;
      if (y >= x)
      {
        y = 0;
        x++;
      }
    }
  }
  clock_gettime(CLOCK_REALTIME, &time2);
  double timeDiff = time2.tv_sec - time1.tv_sec;
  timeDiff += (time2.tv_nsec - time1.tv_nsec) / 1000000000.0;
  printf("Time: %.20f seconds\n", timeDiff);
  // PrintMatrix(testArr, dimension, dimension);
  free(testArr);

  return 0;
}
