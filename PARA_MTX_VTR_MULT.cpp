#include<iostream>
#include<vector>
#include<omp.h>

using namespace std;

vector<int> vectorMatrixMult(const vector<vector<int>> matrix,const vector<int> vec)
{
    int rows = matrix.size();
    int cols = matrix[0].size();
    int v_size = vec.size();
    
    if(cols!=v_size)
    {
        cout<<"Incompatible dimensions can't perform matrix multiplication"<<endl;
        return vector<int>(0);
    }
    
    vector<int> result(rows,0);
    #pragma omp parallel for
    for(int i=0;i<rows;i++)
    {
        #pragma omp parallel for
        for(int j=0;j<cols;j++)
        {
            result[i]+= matrix[i][j]*vec[j];
        }
    }
    return result;
}
void printArray(vector<int> arr)
{
    for(int i=0;i<arr.size();i++)
    {
        cout<<arr[i]<<" ";
    }
}
int main()
{
    vector<vector<int>> mtr={{1,2,3},{4,5,6},{7,8,9}};
    
    vector<int> vec = {1,2,3};
    
    vector<int> result = vectorMatrixMult(mtr,vec);
    printArray(result);
}