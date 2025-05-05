#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>

using namespace std;

const int N = 100; // max nodes
vector<int> graph[N];
bool visited_bfs[N];
bool visited_dfs[N];
int num_threads = 4; // adjust as needed

void addEdge(int u, int v) 
{
    graph[u].push_back(v);
    graph[v].push_back(u); // undirected graph
}

// Parallel BFS using OpenMP
void parallelBFS(int start)
 {
    queue<int> q;
    q.push(start);
    visited_bfs[start] = true;

    cout << "Parallel BFS: ";

    while (!q.empty())
     {
        int size = q.size();
        vector<int> currentLevel;

        // Process current level888
        for (int i = 0; i < size; i++) 
        {
            int node = q.front(); q.pop();
            cout << node << " ";
            currentLevel.push_back(node);
        }

        // Parallelize the neighbor visits
        #pragma omp parallel for num_threads(num_threads)
        for (int i = 0; i < currentLevel.size(); i++) 
        {
            int node = currentLevel[i];
            for (int neighbor : graph[node]) 
            {
                #pragma omp critical
                {
                    if (!visited_bfs[neighbor]) 
                    {
                        visited_bfs[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
        }
    }
    cout << endl;
}

// Parallel DFS using OpenMP Tasks
void parallelDFS(int node) {
    #pragma omp critical
    {
        if (visited_dfs[node]) return;
        visited_dfs[node] = true;
        cout << node << " ";
    }

    #pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < graph[node].size(); i++)
     {
        int neighbor = graph[node][i];
        #pragma omp task
        parallelDFS(neighbor);
    }
}

int main() {
    // Sample graph
    int nodes = 7;
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 5);
    addEdge(1, 3);
    addEdge(2, 4);
    addEdge(3, 6);

    // Parallel BFS
    fill(visited_bfs, visited_bfs + nodes, false);
    parallelBFS(0);

    // Parallel DFS
    fill(visited_dfs, visited_dfs + nodes, false);
    cout << "Parallel DFS: ";
    #pragma omp parallel
    {
        #pragma omp single
        parallelDFS(0);
    }
    cout << endl;

    return 0;
}
