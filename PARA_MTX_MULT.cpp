#include<iostream>
#include<vector>
#include<omp.h>

using namespace std;

vector<vector<int>> matrixMultiplication(const vector<vector<int>> A, const vector<vector<int>> B)
{
    int m = A.size();
    int n = B[0].size();
    int p = B.size();
    
    vector<vector<int>> result(m,vector<int>(n,0));
    
    #pragma omp parallel for collapse(2)
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            for(int k=0;k<p;k++)
            {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

void printMatrix(vector<vector<int>> arr)
{
    int rows = arr.size();
    int cols = arr.size();
    
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
}
int main()
{
    vector<vector<int>> A = {{1,2,3},{4,5,6},{7,8,9}};
    vector<vector<int>> B = {{1,2,3},{4,5,6},{7,8,9}};
    
    vector<vector<int>> result = matrixMultiplication(A,B);
    
    printMatrix(result);
}