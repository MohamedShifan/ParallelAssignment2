#include <stdio.h>
#include <omp.h>

// function to calculate the nth Fibonacci number recursively
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        int x, y;
        #pragma omp task shared(x) firstprivate(n)
        x = fibonacci(n - 1);

        #pragma omp task shared(y) firstprivate(n)
        y = fibonacci(n - 2);

        #pragma omp taskwait
        return x + y;
    }
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    int result;

    double tstart, tstop, tcalc; // Variables for time measurement

    tstart = omp_get_wtime(); // Record start time

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fibonacci(n);
        }
    }

    tstop = omp_get_wtime(); // Record stop time
    tcalc = tstop - tstart; // Calculate time taken

    printf("Fibonacci(%d) = %d\n", n, result);
    printf("Time taken: %.2f seconds\n", tcalc); // Print time taken

    return 0;
}

