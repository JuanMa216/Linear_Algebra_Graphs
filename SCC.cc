#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

class Graph
{
private:
    vector<vector<bool>> adj_matrix;

public:
    Graph(int n) : adj_matrix(n, vector<bool>(n, false)) {}

    void add_edge(int u, int v, int weight)
    {
        if (weight != 0)
        {
            adj_matrix[u][v] = true;
        }
    }
    void print()
    {
        int n = adj_matrix.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (adj_matrix[i][j] == false)
                    cout << setw(4) << ".";
                else
                    cout << setw(4) << adj_matrix[i][j];
            }
            cout << endl;
        }
    }

    void transpuesta()
    {
        int n = adj_matrix.size();
        vector<vector<bool>> transp(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                transp[j][i] = adj_matrix[i][j];
            }
        }
        adj_matrix = transp;
    }

    vector<vector<bool>> pow(const vector<vector<bool>> &A, const vector<vector<bool>> &B)
    {
        int n = A.size();
        vector<vector<bool>> R(n, vector<bool>(n, false));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                    R[i][j] = R[i][j] || (A[i][k] && B[k][j]);
            }
        }
        return R;
    }

    vector<vector<bool>> OR(const vector<vector<bool>> &A, const vector<vector<bool>> &B)
    {
        int n = A.size();
        vector<vector<bool>> result(n, vector<bool>(n));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                result[i][j] = A[i][j] || B[i][j];
            }
        }
        return result;
    }

    vector<vector<bool>> AND(const vector<vector<bool>> &A, const vector<vector<bool>> &B)
    {
        int n = A.size();
        vector<vector<bool>> result(n, vector<bool>(n));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                result[i][j] = A[i][j] && B[i][j];
            }
        }
        return result;
    }

    void SCC()
    {
        int n = adj_matrix.size();
        vector<vector<bool>> A = adj_matrix;
        vector<vector<bool>> C(n, vector<bool>(n, false));

        for (int i = 1; i < n; i++)
        {
            C = OR(C, A);
            A = pow(A, adj_matrix);
        }

        // Transpuesta de C
        vector<vector<bool>> Ct(n, vector<bool>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                Ct[i][j] = C[j][i];

        // SCC = C ∧ Cᵗ
        vector<vector<bool>> SCCs = AND(C, Ct);

        // Imprimir componentes fuertemente conexos
        vector<bool> visited(n, false);
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                vector<int> component;
                for (int j = 0; j < n; j++)
                {
                    if (SCCs[i][j])
                    {
                        component.push_back(j);
                        visited[j] = true;
                    }
                }
                if (!component.empty())
                {
                    cout << "Componente:";
                    for (int v : component)
                        cout << " " << v;
                    cout << endl;
                }
            }
        }
    }
};

int main()
{
    Graph g(8);
    /*Matriz de prueba:
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 1, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 1}
    */

    // Nodo 0
    g.add_edge(0, 0, 0); // 0,1
    g.add_edge(0, 1, 1); // 0,2
    g.add_edge(0, 0, 0); // 0,3
    g.add_edge(0, 0, 0); // 0,4
    g.add_edge(0, 0, 0); // 0,5
    g.add_edge(0, 0, 0); // 0,6
    g.add_edge(0, 0, 0); // 0,7

    // Nodo 1
    g.add_edge(1, 0, 0); // 1,0
    g.add_edge(1, 1, 0); // 1,1
    g.add_edge(1, 2, 1); // 1,2
    g.add_edge(1, 3, 0); // 1,3
    g.add_edge(1, 4, 1); // 1,4
    g.add_edge(1, 5, 1); // 1,5
    g.add_edge(1, 6, 0); // 1,6
    g.add_edge(1, 7, 0); // 1,7

    // Nodo 2
    g.add_edge(2, 0, 0); // 2,0
    g.add_edge(2, 0, 0); // 2,1
    g.add_edge(2, 0, 0); // 2,2
    g.add_edge(2, 3, 1); // 2,3
    g.add_edge(2, 0, 0); // 2,4
    g.add_edge(2, 0, 0); // 2,5
    g.add_edge(2, 6, 1); // 2,6
    g.add_edge(2, 0, 0); // 2,7

    // Nodo 3
    g.add_edge(3, 0, 0); // 3,0
    g.add_edge(3, 0, 0); // 3,1
    g.add_edge(3, 2, 1); // 3,2
    g.add_edge(3, 0, 0); // 3,3
    g.add_edge(3, 0, 0); // 3,4
    g.add_edge(3, 0, 0); // 3,5
    g.add_edge(3, 0, 0); // 3,6
    g.add_edge(3, 7, 1); // 3,7

    // Nodo 4
    g.add_edge(4, 0, 1); // 4,0
    g.add_edge(4, 1, 0); // 4,1
    g.add_edge(4, 2, 0); // 4,2
    g.add_edge(4, 3, 0); // 4,3
    g.add_edge(4, 4, 0); // 4,4
    g.add_edge(4, 5, 1); // 4,5
    g.add_edge(4, 6, 0); // 4,6
    g.add_edge(4, 7, 0); // 4,7

    // Nodo 5
    g.add_edge(5, 0, 0); // 5,0
    g.add_edge(5, 1, 0); // 5,1
    g.add_edge(5, 2, 0); // 5,2
    g.add_edge(5, 3, 0); // 5,3
    g.add_edge(5, 4, 0); // 5,4
    g.add_edge(5, 5, 0); // 5,5
    g.add_edge(5, 6, 1); // 5,6
    g.add_edge(5, 7, 0); // 5,7

    // Nodo 6
    g.add_edge(6, 0, 0); // 6,0
    g.add_edge(6, 1, 0); // 6,1
    g.add_edge(6, 2, 0); // 6,2
    g.add_edge(6, 3, 0); // 6,3
    g.add_edge(6, 4, 0); // 6,4
    g.add_edge(6, 5, 1); // 6,5
    g.add_edge(6, 6, 0); // 6,6
    g.add_edge(6, 7, 1); // 6,7

    // Nodo 7
    g.add_edge(7, 0, 0); // 7,0
    g.add_edge(7, 1, 0); // 7,1
    g.add_edge(7, 2, 0); // 7,2
    g.add_edge(7, 3, 0); // 7,3
    g.add_edge(7, 4, 0); // 7,4
    g.add_edge(7, 5, 0); // 7,5
    g.add_edge(7, 6, 0); // 7,6
    g.add_edge(7, 7, 1); // 7,7

    g.SCC();
    return 0;
}