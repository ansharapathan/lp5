#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>

using namespace std;

// Function to perform sequential bubble sort
void sequentialBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; ++i) {
        for (int j = 0; j < n-i-1; ++j) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

// Function to perform parallel bubble sort using OpenMP
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n-1; ++i) {
        swapped = false;
        #pragma omp parallel for shared(arr, swapped)
        for (int j = 0; j < n-i-1; ++j) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        // If no two elements were swapped in the inner loop, the array is sorted
        if (!swapped) {
            break;
        }
    }
}

// Function to print the elements of the array
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    // Initialize random seed
    srand(time(nullptr));

    // Generate a random array
    vector<int> arr(10000); // Change the array size as needed
    for (int& num : arr) {
        num = rand() % 10000; // Generate random numbers between 0 and 9999
    }

    // Make a copy of the array for parallel sorting
    vector<int> arr_parallel = arr;

    // Measure the execution time of sequential bubble sort
    clock_t start_sequential = clock();
    sequentialBubbleSort(arr);
    clock_t end_sequential = clock();
    double sequential_time = double(end_sequential - start_sequential) / CLOCKS_PER_SEC;

    // Measure the execution time of parallel bubble sort
    clock_t start_parallel = clock();
    parallelBubbleSort(arr_parallel);
    clock_t end_parallel = clock();
    double parallel_time = double(end_parallel - start_parallel) / CLOCKS_PER_SEC;

    // Print the sorted arrays
    cout << "Sequential Bubble Sort: " << sequential_time << " seconds\n";
    cout << "Parallel Bubble Sort: " << parallel_time << " seconds\n";

    return 0;
}
