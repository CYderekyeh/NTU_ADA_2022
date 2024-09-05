#include<bits/stdc++.h>
using namespace std;
#define spIO ios::sync_with_stdio(false);cin.tie(0)
typedef long long ll;
typedef long double ld;
#define DBG(x) cout<<(#x " = ")<<x<<endl;
#define ALL(x) x.begin(),x.end()


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
    spIO;
    int n, m;
    read(n);
    read(m);
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++){
        int u, v, w;
        read(u);
        read(v);
        read(w);
        u--, v--;
        adj[u].emplace_back(v, w);
    }

    ll ans = 2e18;
    for (int i = 0; i < n; i++){
        adj[0].emplace_back(i, 0);
        vector<int> dp(n, 1e9);
        dp[0] = 0;
        queue<int> q;
        q.push(0);
        while (q.size()){
            int u = q.front();
            q.pop();
            for (auto [v, w]:adj[u]){
                if (dp[v] > dp[u] + w){
                    dp[v] = dp[u] + w;
                    q.push(v);
                }
            }
        }
        ll sum = 0;
        for (int j = 0; j < n; j++){
            sum += dp[j];
            // DBG(j);
            // DBG(dp[j]);
        }
        ans = min(ans, sum);
        adj[0].pop_back();
    }

    cout << ans << "\n";
    return 0;
}
