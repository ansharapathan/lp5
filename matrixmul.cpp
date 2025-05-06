#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<omp.h>
using namespace std;


vector<vector<int>> matrixmultiplication(const vector<vector<int>>& A,const vector<vector<int>>& B)
{
    int m=A.size();
    int p=A[0].size();
    int n=B[0].size();

    vector<vector<int>> result(m,vector<int>(n,0));
    #pragma omp parallel for collapse(2)

    for(int i=0;i<m;i++)

    {
        for(int j=0;j<n;j++)
        {
            for(int k=0;k<p;k++)
            {
               result[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
   return( result);
}

void printmatrix(const vector<vector<int>>& matrix)
{

    for(const auto& row:matrix)
    {
       for(int val:row)
       {
        cout<<val<<" ";
       
       }
       cout<<endl;
    }
    cout<<endl;


}
int main()
{
    srand(time(0));

    int m=3+rand()%3;
    int n=3+rand()%3;
    int p=3+rand()%3;

    vector<vector<int>> A(m,vector<int>(n));
    


    for(int i=0;i<m;++i)
    {
        for(int j=0;j<n;++j)
        {
           A[i][j]=rand()%10;
        }
    }

    vector<vector<int>> B(n,vector<int>(p));
    for(int i=0;i<n;++i)
    {
        for(int j=0;j<p;++j)
        {
           B[i][j]=rand()%10;
        }
    }

    cout<<"matrix A"<<endl;
    printmatrix(A);
    printmatrix(B);

    vector<vector<int>> result=matrixmultiplication(A,B);
    printmatrix(result);
}