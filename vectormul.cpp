#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<omp.h>

using namespace std;

vector<int> multi(const vector<vector<int>>& metrics,const vector<int>& vec)
{
    int row=metrics.size();
    int column=metrics[0].size();

    if(column!=vec.size())
        return{};

    vector<int> result(row,0);

    #pragma omp parallel for
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<column;j++)
        {
            result[i]+=metrics[i][j]*vec[j];
        }
    }
    return (result);

}

void printmetrics(vector<vector<int>>& metrics)
{
    for(const auto& row : metrics)
    {
        for(int val:row)
        {
            cout<<val<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
void printvector(vector<int>& vec)
{
    for(int val:vec)
       cout<<val<<" ";
    cout<<endl;
}

int main()
{
    srand(time(0));

    int row=3+rand()%3;
    int col=3+rand()%3;

    vector<vector<int>> metrics(row,vector<int>(col));
    for(int i=0;i<row;++i)
        for(int j=0;j<col;++j)
            metrics[i][j]=rand()%10;

    vector<int> vec(col);
    for(int i=0;i<col;++i)
    vec[i]=rand()%10;

    
   cout<<"vector"<<endl;
    printvector(vec);
    cout<<"mtrics"<<endl;
    printmetrics(metrics);

    vector <int>result=multi(metrics,vec);

    printvector(result);
}