#include <stdio.h>
#include <stdlib.h>
#include <cblas.h>
#include <time.h>

double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

int main() {
    // Matrix dimensions
    int m = 256, n = 256, k = 256;

    // Allocate memory for matrices
    float *A = (float *)malloc(m * k * sizeof(float));
    float *B = (float *)malloc(k * n * sizeof(float));
    float *C = (float *)malloc(m * n * sizeof(float));

    // Initialize matrix values (example)
    for (int i = 0; i < m * k; i++) {
        A[i] = i + 1;
    }
    for (int i = 0; i < k * n; i++) {
        B[i] = i + 1;
    }

    double start, finish, total;

    // Perform matrix multiplication using cblas_sgemm
    start = CLOCK();
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, k, 1.0f, A, k, B, n, 0.0f, C, n); 
    finish = CLOCK();
    total = finish-start;

    // Print the result matrix C
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f ", C[i * n + j]);
        }
        printf("\n");
    }
    printf("The total time for matrix multiplication = %f ms\n", total);

    // Free allocated memory
    free(A);
    free(B);
    free(C);

    return 0;
}
