#include<bits/stdc++.h>
using namespace std;
#define spIO ios::sync_with_stdio(false);cin.tie(0)
typedef long long ll;
typedef long double ld;
#define DBG(x) cout<<(#x " = ")<<x<<endl;
#define ALL(x) x.begin(),x.end()



int main(){
    spIO;
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> root;
    for (int i = 0; i < n; i++){
        int fa;
        cin >> fa;
        if (fa == -1){
            root.push_back(i);
        }else{
            adj[fa].push_back(i);
        }
    }
    vector<int> c(n), d(n);
    for (int i = 0; i < n; i++){
        cin >> c[i] >> d[i];
    }
    vector<int> sub(n), sz(n);
    function<void(int)> dfs = [&](int u){
        sz[u] = 1;
        sub[u] = c[u];
        for (int v:adj[u]){
            dfs(v);
            sub[u] += sub[v];
            sz[u] += sz[v];
        }
    };
    for (int r:root){
        dfs(r);
    }

    vector<vector<int>> dps(n, vector<int>(m+1, -1));
    vector<int> dp_base(m+1, -1);
    dp_base[0] = 0;

    vector<int> tout(n);
    int timer = 0;
    function<void(int)> dfs_ans = [&](int u){
        for (int v:adj[u]){
            dfs_ans(v);
        }

        auto get_dp = [&](int x){
            if (x == -1) return dp_base;
            else return dps[x];
        };

        tout[u] = timer++;
        auto &dp = dps[tout[u]];
        auto tmp = get_dp(tout[u] - 1);
        for (int i = m; i >= 0; i--){
            dp[i] = max(dp[i], tmp[i]);
        }

        for (int i = m; i >= c[u]; i--){
            if (tmp[i - c[u]] != -1){
                dp[i] = max(dp[i], tmp[i - c[u]] + c[u]);
            }
        }

        tmp = get_dp(tout[u] - sz[u]);
        for (int i = m; i >= d[u]; i--){
            if (tmp[i - d[u]] != -1){
                dp[i] = max(dp[i], tmp[i - d[u]] + sub[u]);
            }
        }
    };
    for (int r:root){
        dfs_ans(r);
    }
    assert(timer == n);
    int ans = *max_element(ALL(dps[n-1]));
    assert(ans >= 0);
    cout << ans << "\n";
    return 0;
}
