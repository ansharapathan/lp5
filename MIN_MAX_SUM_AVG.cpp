#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Function to find the minimum element in an array
int parallelMin(const vector<int>& arr) {
    int min_val = arr[0];
    
    #pragma omp parallel for reduction(min:min_val)
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    
    return min_val;
}

// Function to find the maximum element in an array
int parallelMax(const vector<int>& arr) {
    int max_val = arr[0];
    
    #pragma omp parallel for reduction(max:max_val)
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    
    return max_val;
}

// Function to compute the sum of elements in an array
int parallelSum(const vector<int>& arr) {
    int sum = 0;
    
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); ++i) {
        sum += arr[i];
    }
    
    return sum;
}

// Function to compute the average of elements in an array
double parallelAverage(const vector<int>& arr) {
    int sum = parallelSum(arr);
    double avg = static_cast<double>(sum) / arr.size();
    return avg;
}

int main() {
    vector<int> arr = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    
    // Find the minimum element
    int min_val = parallelMin(arr);
    cout << "Minimum: " << min_val << endl;
    
    // Find the maximum element
    int max_val = parallelMax(arr);
    cout << "Maximum: " << max_val << endl;
    
    // Compute the sum of elements
    int sum = parallelSum(arr);
    cout << "Sum: " << sum << endl;
    
    // Compute the average of elements
    double avg = parallelAverage(arr);
    cout << "Average: " << avg << endl;
    
    return 0;
}
