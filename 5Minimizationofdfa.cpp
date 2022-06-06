#include <bits/stdc++.h>
using namespace std;
const int N = 109;
int t[N][N]; // transition table
bool fs[N];  // final states
bool printed[N];
vector<vector<int>> pi[2]; // set of equivalence classes
int n, m, nfs;
int idx(int x)
{
    for (int i = 0; i < pi[0].size(); i++)
    {
        for (int j = 0; j < pi[0][i].size(); j++)
        {
            if (pi[0][i][j] == x)
                return i;
        }
    }
}
void print_min()
{
    cout << "\n Minimised DFA Table:\n";
    cout << "---------------------\n";
    cout << "Q\t";
    for (int j = 0; j < m; j++)
        cout << j << "\t";
    cout << endl
         << endl;
    for (int i = 0; i < n; i++)
    {
        if (printed[i] == 1)
            continue;
        int ind = idx(i);
        cout << "[";
        for (int k = 0; k < pi[0][ind].size(); k++)
        {
            cout << pi[0][ind][k];
            printed[k] = 1;
        }
        cout << "]\t";
        for (int j = 0; j < m; j++)
        {
            ind = idx(t[i][j]);
            cout << "[";
            for (int k = 0; k < pi[0][ind].size(); k++)
            {
                cout << pi[0][ind][k];
            }
            cout << "]\t";
        }
        cout << endl;
    }
    cout << endl;
}
int main()
{
    cout<<endl;
    cout<<"Name :Shreyas Mishra\n”"<<endl;
    cout<<"Roll No : UE193104"<<endl;
    n = 5, m = 2;
    nfs = 1;
    fs[4] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> t[i][j];
        }
    }
    vector<int> v[2];
    for (int i = 0; i < n; i++)
    {
        v[fs[i]].push_back(i);
    }
    pi[0].push_back(v[0]);
    pi[0].push_back(v[1]);
    pi[1] = pi[0];
    int iters = 100;
    while (iters--)
    {
        pi[0] = pi[1];
        for (int i = 0; i < pi[1].size(); i++)
        {
            for (int j = 1; j < pi[1][i].size(); j++)
            {
                bool placed = 0;
                for (int k = 0; k < j; k++)
                {
                    bool compat = 1;
                    for (int l = 0; l < m; l++)
                    {
                        if (idx(t[pi[1][i][j]][l]) != idx(t[pi[1][i][k]][l]))
                        {
                            compat = 0;
                            break;
                        }
                    }
                    if (compat)
                    {
                        placed = 1;
                        break;
                    }
                }
                if (placed)
                    continue;
                for (int x = pi[0].size(); x < pi[1].size(); x++)
                {
                    for (int k = 0; k < pi[1][x].size(); k++)
                    {
                        bool compat = 1;
                        for (int l = 0; l < m; l++)
                        {
                            if (idx(t[pi[1][i][j]][l]) != idx(t[pi[1][x][k]][l]))
                            {
                                compat = 0;
                                break;
                            }
                        }
                        if (compat)
                        {
                            pi[1][x].push_back(pi[1][i][j]);
                            pi[1][i].erase(pi[1][i].begin() + j);
                            placed = 1;
                            break;
                        }
                    }
                    if (placed)
                        break;
                }
                if (placed)
                    continue;
                vector<int> vv;
                vv.push_back(pi[1][i][j]);
                pi[1].push_back(vv);
                pi[1][i].erase(pi[1][i].begin() + j);
            }
        }
        for (int i = 0; i < pi[0].size(); i++)
        {
            sort(pi[0][i].begin(), pi[0][i].end());
        }
        sort(pi[0].begin(), pi[0].end());
        for (int i = 0; i < pi[1].size(); i++)
        {
            sort(pi[1][i].begin(), pi[1][i].end());
        }
        sort(pi[1].begin(), pi[1].end());
        if (pi[0] == pi[1])
            break;
    }
    assert(pi[0] == pi[1]);
    print_min();
    return 0;
}

