#include <stdio.h>
#include <omp.h>

void parallelBubbleSort(int arr[], int n) {
    int temp;
    int swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = 0; // adding a flag variable to optimize the loop

        #pragma omp parallel for shared(arr, swapped)
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) { // swapping arr[j] and arr[j + 1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1; // changing the flag if a swap occurred
            }
        }
        // the array is in the sorted form when no values swapped
        if (swapped == 0) {
            break;
        }
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    double tstart, tstop, tcalc; // Variables for time measurement

    tstart = omp_get_wtime(); // Record start time

    parallelBubbleSort(arr, n);

    tstop = omp_get_wtime(); // Record stop time
    tcalc = tstop - tstart; // Calculate time taken

    printf("\nSorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\nTime taken: %.2f seconds\n", tcalc); // Print time taken

    return 0;
}
