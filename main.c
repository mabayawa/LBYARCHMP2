#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Assembly kernel function here
// extern void calculate_distances_asm(int n, double *x1, double *x2, double *y1, double *y2, double *z);
extern double asm_distance(double x1, double x2, double y1, double y2);

// C kernel function
void c_distance(int n, double *x1, double *x2, double *y1, double *y2, double *z) {
    int i;
    for (i = 0; i < n; i++) {
        z[i] = sqrt(pow(x2[i] - x1[i], 2) + pow(y2[i] - y1[i], 2));
    }
}



// main timing
int main() {
    const int vector_sizes[] = {1 << 20, 1 << 24, 1 << 25}; // crashes at 28 idk
	int i, j, k;
    srand(time(NULL));
    double test_value1 = (double)(rand() % 100) / 10.0;
    double test_value2 = (double)(rand() % 100) / 10.0;
    double test_value3 = (double)(rand() % 100) / 10.0;
    double test_value4 = (double)(rand() % 100) / 10.0;
	
    for (k = 0; k < 3; k++) {
        int runs = 30;
        int n = vector_sizes[k];

        double *x1 = (double *)malloc(n * sizeof(double));
        double *x2 = (double *)malloc(n * sizeof(double));
        double *y1 = (double *)malloc(n * sizeof(double));
        double *y2 = (double *)malloc(n * sizeof(double));
        double *z_c = (double *)malloc(n * sizeof(double));
        double *z_asm = (double *)malloc(n * sizeof(double));
        
        for (i = 0; i < n; i++) {
            x1[i] = test_value1;
            x2[i] = test_value2;
            y1[i] = test_value3;
            y2[i] = test_value4;
        }

        // C kernel
        clock_t s, e;
        double c_time = 0.0;
        for (i = 0; i < runs; i++) {
            s = clock();
            c_distance(n, x1, x2, y1, y2, z_c);
            e = clock();
            c_time += (double)(e - s) / CLOCKS_PER_SEC;
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
        double asm_time = 0.0;
        for (i = 0; i < runs; i++) {
            s = clock();
            // calculate_distances_asm(n, x1, x2, y1, y2, z_asm);
            for (j = 0; j < n; j++) {
                z_asm[j] = asm_distance(x1[j], x2[j], y1[j], y2[j]);
            }
            e = clock();
            asm_time += (double)(e - s) / CLOCKS_PER_SEC;
        }
        asm_time /= runs;


        printf("\nASSEMBLY KERNEL RESULT (FIRST 10 ELEMENTS):\n");
        for (i = 0; i < 10; i++) {
            printf("Z[%d] = %f\n", i, z_asm[i]);
        }
        printf("> ASSEMBLY KERNEL AVERAGE TIME: %f seconds\n", asm_time);

        printf("\nSANITY CHECK\n");
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


/*
nasm -f win64 test_asm.asm
gcc -c main.c -o cfile.obj -m64
gcc cfile.obj test_asm.obj -o cfile.exe -m64
cfile.exe
*/