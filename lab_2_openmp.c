#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_NUM_THREADS 128
#define MAX_MATRIX_SIZE 8192

int DimensionsToLength(int size)
{  return size*size; }

void PrintMatrix(int *arr, int size)
{
  int length = DimensionsToLength(size);
  for (size_t i = 0; i < length; i++)
  {
    printf("%d\t", arr[i]);
    if ((i+1) % size == 0)
      printf("\n");
  }
  printf("\n");
}

void SetNumber(int *arr, int size)
{
  int length = DimensionsToLength(size);

  for (int i = 0; i < length; i++)
  {
    arr[i] = i+1;
  }
}

int main(int argc, char const *argv[])
{
  int *testArr = malloc(DimensionsToLength(MAX_MATRIX_SIZE)*sizeof(int));
  SetNumber(testArr, MAX_MATRIX_SIZE);
  for (int dimension = 128; dimension <= MAX_MATRIX_SIZE; dimension *= 8)
  {
    for (int numThreads = 4; numThreads <= MAX_NUM_THREADS; numThreads *= 2)
    {
      int swapLength = (dimension*(dimension - 1)) / 2;
      int iterationsPerThread = swapLength / numThreads;

      int extraWorkThreads = swapLength % numThreads;
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
      #pragma omp parallel shared(extraWorkThreads, testArr, dimension, iterationsPerThread) private(x, y, threadID, rawPos, swapIteration, _iterationsPerThread, temp, i) num_threads(numThreads)
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
      printf("%dx%d\t%d\t%.10f\n", dimension, dimension, numThreads, timeDiff);
    }
    printf("----------------------------------------------\n");
  }

  free(testArr);

  return 0;
}
