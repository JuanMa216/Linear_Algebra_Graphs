#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class Graph
{
private:
    vector<vector<int>> adj_matrix;

public:
    Graph(int n) : adj_matrix(n, vector<int>(n, -1)) {}

    void add_edge(int u, int v, int weight)
    {
        if (u == v || adj_matrix[u][v] != -1)
            return;
        adj_matrix[u][v] = weight;
    }

    void print()
    {
        int n = adj_matrix.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (adj_matrix[i][j] == -1)
                    cout << setw(4) << ".";
                else
                    cout << setw(4) << adj_matrix[i][j];
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g(4);
    g.add_edge(0, 1, 2);
    g.add_edge(0, 2, 2);
    g.add_edge(0, 3, 2);
    g.add_edge(1, 0, 2);
    g.print();
}