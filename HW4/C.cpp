#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline void rit(T& x) {
  char c = 0; bool flag = false;
  while (c = getchar(), (c < '0') || c > '9') if (c == -1) return;
  x = c - '0';
  while (c = getchar(), c >= '0' && c <= '9') x = x * 10 + c - '0';
  if (flag) x = -x;
}

const int maxn = 405;
long long dp[maxn][maxn];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    rit(n);
    // cin >> n;
    vector<vector<int>> mat(n, vector<int>(n));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            rit(mat[i][j]);
            // cin >> mat[i][j];
        }
    }
    // first cut {0...d}, {d+1 ... n-1}
    vector<long long> res(n);
    for (int d = 0; d < n; d++){
        // vector<vector<long long>> dp(n, vector<long long>(n, -1));
        memset(dp, -1, sizeof(dp));
        int ed = (d+1 < n ? d+1 : 0);
        dp[0][ed] = 0;
        for (int i = 0; i+1 < n; i++){
            for (int j = d+1; j < n; j++){
                if (dp[i][j] == -1){
                    continue;
                }
                // dp[i][j] -> dp[i+1][k]
                for (int k = j; k < n; k++){
                    int to = (k+1 < n ? k+1 : 0);
                    dp[i+1][to] = max(dp[i+1][to], dp[i][j] + mat[j][to]);
                }
            }
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                // update res
                if (dp[i][j] != -1){
                    res[i] = max(res[i], dp[i][j] + mat[j][ed]);
                }
            }
        }
    }
    for (int i = 0; i < n; i++){
        cout << res[i] << ' ';
    }
    return 0;
}