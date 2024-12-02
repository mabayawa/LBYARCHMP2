#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Assembly kernel function here
extern void calculate_distances_asm(int n, float *x1, float *x2, float *y1, float *y2, float *z);

// C kernel function
void c_distance(int n, float *x1, float *x2, float *y1, float *y2, float *z) {
    int i;
    for (i = 0; i < n; i++) {
        z[i] = sqrtf((x2[i] - x1[i]) * (x2[i] - x1[i]) + (y2[i] - y1[i]) * (y2[i] - y1[i]));
    }
}

float check_distance(float x1, float y1, float x2, float y2){
  return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
 }

// main timing
int main() {
    const int vector_sizes[] = {1 << 20, 1 << 24, 1 << 27}; // crashes at 28 idk
	int i, j, k;
    srand(time(NULL));
    float test_value1 = (float)(rand() % 100) / 20.0;
    float test_value2 = (float)(rand() % 100) / 20.0;
    float test_value3 = (float)(rand() % 100) / 20.0;
    float test_value4 = (float)(rand() % 100) / 20.0;
    float c_sanity_key = check_distance(test_value1, test_value2, test_value3, test_value4);

    for (k = 0; k < 3; k++) {
        int runs = 30;
        int n = vector_sizes[k];

        float *x1 = (float *)malloc(n * sizeof(float));
        float *x2 = (float *)malloc(n * sizeof(float));
        float *y1 = (float *)malloc(n * sizeof(float));
        float *y2 = (float *)malloc(n * sizeof(float));
        float *z_c = (float *)malloc(n * sizeof(float));
        float *z_asm = (float *)malloc(n * sizeof(float));

        for (i = 0; i < n; i++) {
            x1[i] = test_value1;
            x2[i] = test_value2;
            y1[i] = test_value3;
            y2[i] = test_value4;
        }

        // C kernel
        clock_t s, e;
        float c_time = 0.0;
        for (i = 0; i < runs; i++) {
            s = clock();
            c_distance(n, x1, x2, y1, y2, z_c);
            e = clock();
            c_time += (float)(e - s) / CLOCKS_PER_SEC;
        }
        c_time /= runs;


        printf("\n=== VECTOR SIZE: 2^%d (n = %d) ===\n", (int)(log2(n)), n);
        printf("x1 x2 y1 y2 (FIRST 10 ELEMENTS):\n");
        for (i = 0; i < 10; i++) {
            printf("x1[%d] = %f x2[%d] = %f y1[%d] = %f y2[%d] = %f\n",
                   i, x1[i], i, x2[i], i, y1[i], i, y2[i]);
        }

        printf("\nC KERNEL RESULT (FIRST 10 ELEMENTS):\n");
        for (i = 0; i < 10; i++) {
            printf("Z[%d] = %f\n", i, z_c[i]);
        }
        printf("> C KERNEL AVERAGE TIME: %f seconds\n", c_time);

        // assembly kernel
        float asm_time = 0.0;
        for (i = 0; i < runs; i++) {
            s = clock();
            calculate_distances_asm(n, x1, x2, y1, y2, z_asm);
            e = clock();
            asm_time += (float)(e - s) / CLOCKS_PER_SEC;
        }
        asm_time /= runs;


        printf("\nASSEMBLY KERNEL RESULT (FIRST 10 ELEMENTS):\n");
        for (i = 0; i < 10; i++) {
            printf("Z[%d] = %f\n", i, z_asm[i]);
        }
        printf("> ASSEMBLY KERNEL AVERAGE TIME: %f seconds\n", asm_time);

        printf("\nSANITY CHECK x86-64\n");
        for (i = 0; i < 10; i++) {
            if (z_asm[i] == z_c[i]) {
              printf("Z[%d] : THE x86-64 KERNEL OUTPUT IS CORRECT\n", i);
            }
            else {
              printf("Z[%d] : FAILED\n", i);
            }
        }

        // free the allocated mem
        free(x1);
        free(x2);
        free(y1);
        free(y2);
        free(z_c);
        free(z_asm);
    }

    return 0;
}