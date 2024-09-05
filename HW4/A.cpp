#include "ypglpk.hpp"
#include <bits/stdc++.h>
using namespace std;

struct Edge{
    int u, v, w;
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ypglpk::set_output(false);
    int n, m;
    cin >> n >> m;
    vector<Edge> ed(m);
    vector<vector<int>> in(n), out(n);
    for (int i = 0; i < m; i++){
        cin >> ed[i].u >> ed[i].v >> ed[i].w;
        ed[i].u--, ed[i].v--;
        out[ed[i].u].push_back(i);
        in[ed[i].v].push_back(i);
    }   
    // n: order of vertexes (1....n)
    // m: whether choosing this edge or not {0, 1} 
    vector<vector<double>> A(n*3+m, vector<double>(n+m));
    vector<double> B(n*3+m), C(n+m);
    // For each vertex = {2...n-1}, sigma(in - out) = 0
    // For vertex = 1, n, sigma(in - out) = -1, 1
    // For each vertex = {1...n-1}, sigma(out) = 1, otherwise 0
    for (int i = 0; i < n; i++){
        for (auto &id:in[i]){
            A[i][id] = 1;
            A[i+n][id] = -1;
        }
        for (auto &id:out[i]){
            A[i][id] = -1;
            A[i+n][id] = 1;
            A[i+2*n][id] = 1;
        }
        if (i == 0){
            B[i] = -1;
            B[i+n] = 1;
            B[i+2*n] = 1;
        }else if (i == n-1){
            B[i] = 1;
            B[i+n] = -1;
            B[i+2*n] = 0;
        }else{
            B[i+2*n] = 1;
        }
    }
    // e.u - e.v + 1000 * e <= 999, prevent cycles
    for (int i = 0; i < m; i++){
        A[i+3*n][i] = 10000;
        A[i+3*n][m+ed[i].u] = 1;
        A[i+3*n][m+ed[i].v] = -1;
        B[i+3*n] = 9999;
    }
    for (int i = 0; i < m; i++){
        C[i] = ed[i].w;
    }
    vector<int> vartype(n+m);
    for (int i = 0; i < n+m; i++){
        if (i < m){
            vartype[i] = GLP_BV;
        }else{
            vartype[i] = GLP_IV;
        }
    }
    // for (int i = 0; i < 3*n+m; i++){
    //     for (int j = 0; j < n+m; j++){
    //         cout << A[i][j] << " \n"[j==n+m-1];
    //     }
    // }
    // for (int i = 0; i < 3*n+m; i++){
    //     cout << B[i] << " \n"[i==3*n+m-1];
    // }
    // for (int i = 0; i < n+m; i++){
    //     cout << C[i] << " \n"[i==n+m-1];
    // }   
    pair<double, vector<double>> res;
    res = ypglpk::mixed_integer_linear_programming(A, B, C, vartype);
    if (res.first == -ypglpk::INF){
        cout << -1 << "\n";
    }else{
        cout << (int) res.first << "\n";
        for (int i = 0; i < m; i++){
            cout << (int)res.second[i];
        }
        cout << "\n";
    }
    return 0;
}