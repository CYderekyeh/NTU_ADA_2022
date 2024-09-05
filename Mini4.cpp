#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline bool read(T& x) {
  char c = 0; bool flag = false;
  while (c = getchar(), (c < '0' && c != '-') || c > '9') if (c == -1) return false;
  c == '-' ? (flag = true, x = 0) : (x = c - '0');
  while (c = getchar(), c >= '0' && c <= '9') x = x * 10 + c - '0';
  if (flag) x = -x;
  return true;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    read(n);
    read(m);
    vector<vector<int>> adj(n), radj(n);
    for (int i = 0; i < m; i++){
        int u, v;
        read(u);
        read(v);
        u--, v--;
        adj[u].push_back(v);
    }

    long long ans = 0;
    vector<int> dfn(n), low(n), ins(n);
    int timer = 0;
    stack<int> stk;
    function<void(int)> tarjan = [&](int u){
        low[u] = dfn[u] = ++timer;
        ins[u] = true;
        stk.push(u);
        for (int v:adj[u]){
            if (!dfn[v]){
                tarjan(v);
                low[u] = min(low[u], low[v]);
            }else if (ins[v]){
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]){
            int v;
            long long cnt = 0;
            do {
                v = stk.top(); stk.pop();
                cnt++;
                ins[v] = false;
            } while(v != u);
            ans += cnt * (cnt - 1) / 2;
        }
    };
    for (int i = 0; i < n; i++){
        if (!dfn[i]){
            tarjan(i);
        }
    }
    cout << ans << "\n";
    return 0;
}