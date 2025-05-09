#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define N 512        
#define LOOPS 10        
#define NB 64

double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

int main()
{
  double a[N][N]; /* input matrix */
  double b[N][N]; /* input matrix */
  double c[N][N]; /* result matrix */
  int i, j, k, l, num_zeros, ii, jj, kk, b_size;
  double start, finish, total;


  /* initialize a dense matrix */
  for(i=0; i<N; i++){    
    for(j=0; j<N; j++){
      a[i][j] = (double)(i+j);
      b[i][j] = (double)(i-j);
    }
  }
  
  printf("starting dense matrix multiply \n");
  start = CLOCK();
  /*
  for(i=0; i<N; i++)
    for(j=0; j<N; j++){
      c[i][j] = 0.0;
      for(k=0; k<N; k++)  
        c[i][j] = c[i][j] + a[i][k] * b[k][j]; 
     }  
     */
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      c[i][j] = 0;
    }
  }
  b_size = N / NB;
  for (ii = 0; ii < NB; ii++) {
    for (jj = 0; jj < NB; jj++) {
      for (kk = 0; kk < NB; kk++) {
        for (i = ii * b_size; i < (ii + 1) * b_size; i++) {
          for (j = jj * b_size; j < (jj + 1) * b_size; j++) {
            for (k = kk * b_size; k < (kk + 1) * b_size; k++) {
              c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
          }
        }
      }
    }
  }

finish = CLOCK();

total = finish-start;
printf("a result %g \n", c[7][8]); /* prevent dead code elimination */
printf("The total time for matrix multiplication with dense matrices = %f ms\n", total);

  /* initialize a sparse matrix */
  num_zeros = 0; 
  for(i=0; i<N; i++){    
    for(j=0; j<N; j++){
      if ((i<j)&&(i%2>0))
        {
         a[i][j] = (double)(i+j);
         b[i][j] = (double)(i-j);
        }
      else
        { 
         num_zeros++;
         a[i][j] = 0.0;
         b[i][j] = 0.0;
        }
       
     }
  }

  printf("starting sparse matrix multiply \n");
  start = CLOCK();
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      c[i][j] = 0;
    }
  }
  b_size = N / NB;
  for (ii = 0; ii < NB; ii++) {
    for (jj = 0; jj < NB; jj++) {
      for (kk = 0; kk < NB; kk++) {
        for (i = ii * b_size; i < (ii + 1) * b_size; i++) {
          for (j = jj * b_size; j < (jj + 1) * b_size; j++) {
            for (k = kk * b_size; k < (kk + 1) * b_size; k++) {
              c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
          }
        }
      }
    }
  }
finish = CLOCK();
total = finish-start;
printf("A result %g \n", c[7][8]); /* prevent dead code elimination */
printf("The total time for matrix multiplication with sparse matrices = %f ms\n", total);
printf("The sparsity of the a and b matrices = %f \n", (float)num_zeros/(float)(N*N));

return 0;
}

