#include <bits/stdc++.h>
using namespace std;


struct Edge {
    int u, v, w;
};
struct DSU{
    vector<int> p, sz;
    int n;
    DSU (int _n): n(_n){
        p.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++){
            p[i] = i;
            sz[i] = 1;
        }
    }
    int find(int x){
        if (p[x] == x) return x;
        else return p[x] = find(p[x]);
    }
    bool merge(int x, int y){
        x = find(x), y = find(y);
        if (x == y) return false;
        if (sz[x] > sz[y]) swap(x, y);
        p[x] = y;
        sz[y] += sz[x];
        return true;
    }
};
template <typename T>
inline bool rit(T& x) {
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
    rit(n);
    rit(m);
    vector<Edge> ed(m);
    for (int i = 0; i < m; i++){
        rit(ed[i].u);
        rit(ed[i].v);
        rit(ed[i].w);
        // cin >> ed[i].u >> ed[i].v >> ed[i].w;
        ed[i].u--, ed[i].v--;
    }
    sort(ed.begin(), ed.end(), [&](Edge a, Edge b){
        return a.w < b.w;
    });
    DSU d(n);
    long long ans = 0;
    for (auto &[u, v, w]:ed){
        if (d.merge(u, v)){
            ans += w;   
        }
    }
    cout << ans << "\n";
}