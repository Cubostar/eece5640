#include <stdio.h>
#include <x86intrin.h>
#include <stdlib.h>
#include <time.h>

double CLOCK() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC,  &t);
        return (t.tv_sec * 1000)+(t.tv_nsec*1e-6);
}

float dot_product(const float *vec1, const float *vec2, size_t size) {
    double result = 0.0;
    for (int i = 0; i < size; i++) {
        result += vec1[i] * vec2[i];
    }
    return result;
}

float* matrix_vector(const float** mat, const float* vec, size_t size) {
    float* result = malloc(size * sizeof(*result));
    for (int i = 0; i < size; i++) {
        result[i] = dot_product(mat[i], vec, size); 
    }
    return result;
}

float dot_product_avx512f(const float *a, const float *b, size_t len) {

    size_t i = 0;
    float sum_arr[16];

    __m512 sum_vec, a_vec, b_vec;
    
    sum_vec = _mm512_setzero_ps();

    for (; i + 16 <= len; i += 16) {
        a_vec = _mm512_loadu_ps(&a[i]);
        b_vec = _mm512_loadu_ps(&b[i]);
        sum_vec = _mm512_fmadd_ps(a_vec, b_vec, sum_vec);
    }

    _mm512_storeu_ps(sum_arr, sum_vec);
    float total_sum = 0.0f;
    for (int j = 0; j < 16; j++) {
        total_sum += sum_arr[j];
    }

    for (; i < len; i++) {
        total_sum += a[i] * b[i];
    }

    return total_sum;
}

int main() {

#define N 4096

double start, finish, total;
float* result;
int i, j;
float** a = malloc(N & sizeof(*a)); 
float b[N];
size_t len = sizeof(b)/sizeof(b[0]);	
//    size_t len = sizeof(a) / sizeof(a[0]);

for (i=0; i< N; i++) {
	b[i] = 1.0;
        a[i] = malloc(N * sizeof(*a[i]));
        for (j=0; j< N; j++) {
            a[i][j] = 1.0;
        }
}

    /*
start = CLOCK();

result = matrix_vector_avx512f(a, b, len);

finish = CLOCK();
total = finish-start;
printf("Matrix-vector result = %f \n", result);
printf("The total time for matrix multiplication with AVX = %f ms\n", total);
*/

start = CLOCK();

result = matrix_vector(a, b, len);

finish = CLOCK();
total = finish-start;
printf("Matrix-vector result = %f \n", result[0]); /* prevent dead code elimination */
printf("The total time for matrix multiplication without AVX = %f ms\n", total);
    return 0;
}
