#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_NUM_THREADS 128
#define MAX_MATRIX_SIZE 8192

int DimensionsToLength(int size)
{  return size*size; }

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

void SetNumber(int *arr,int size)
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
  pthread_t threads[MAX_NUM_THREADS - 1];
  for (int dimension = 128; dimension <= MAX_MATRIX_SIZE; dimension *= 8)
  {
    for (int numThreads = 4; numThreads <= MAX_NUM_THREADS; numThreads *= 2)
    {
      int swapLength = (dimension*(dimension - 1)) / 2;
      int iterationsPerThread = swapLength / numThreads;

      double rawPos;
      int extraWorkThreads = swapLength % numThreads;

      int x;
      int threadNo = 0;
      int thread;

      struct timespec time1, time2;

      clock_gettime(CLOCK_REALTIME, &time1);
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
        if (i >= swapLength - iterationsPerThread)
        {
          int temp;
          int y = threadArgsArray[threadNo].yStart;
          for (size_t i = 0; i < threadArgsArray[threadNo].iterations; i++)
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
        else
        {
          thread = pthread_create(&threads[threadNo], NULL, DoSwaps, (void *)&threadArgsArray[threadNo]);
          if (thread)
          {
              printf("ERROR; return code from pthread_create() is %d\n", thread);
              exit(-1);
          }
          threadNo++;
        }
      }

      void *status;
      int rc;
      for(size_t t = 0; t < numThreads - 1; t++)
      {
        rc = pthread_join(threads[t], &status);
        if (rc)
        {
          printf("ERROR; return code from pthread_join() is %d\n", rc);
          exit(-1);
        }
      }
      clock_gettime(CLOCK_REALTIME, &time2);
      double timeDiff = time2.tv_sec - time1.tv_sec;
      timeDiff += (time2.tv_nsec - time1.tv_nsec) / 1000000000.0;  printf("%dx%d\t%d\t%.10f\n", dimension, dimension, numThreads, timeDiff);
    }
    printf("----------------------------------------------\n");
  }
  pthread_exit(NULL);
  free(testArr);

  return 0;
}
