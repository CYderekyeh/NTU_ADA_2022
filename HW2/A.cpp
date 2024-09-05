#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pi;
typedef pair<ll,ll> pl;
typedef pair<ld,ld> pd;

typedef vector<int> vi;
typedef vector<ld> vd;
typedef vector<ll> vl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<cd> vcd;

template<class T> using pq = priority_queue<T>;
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

#define sz(x) (int)(x).size()
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define ins insert

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ", "; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? ", " : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifdef DEBUG
#define dbg(x...) cerr << "\e[91m"<<__func__<<":"<<__LINE__<<" [" << #x << "] = ["; _print(x); cerr << "\e[39m" << endl;
#else
#define dbg(x...)
#endif

const int maxn = 1005, maxk = 505;

ll a[maxn], s[maxn];
ll c[maxn][maxn];
ll dp[maxk][maxn];


void go(int k, int l, int r, int lo, int hi){
    if (r < l) return;
    int m = (l + r) >> 1;
    int pos = 0;
    for (int i = lo; i <= hi && i + 1 <= m; i++){
        if (dp[k-1][i] + c[i+1][m] < dp[k][m]){
            dp[k][m] = dp[k-1][i] + c[i+1][m];
            pos = i;
        }
    }
    go(k, l, m-1, lo, pos);
    go(k, m+1, r, pos, hi);
}

void solve(){
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++){
        s[i] = s[i-1] + a[i];
    }

    for (int i = 1; i <= n; i++){
        for (int j = i; j <= n; j++){
            c[i][j] = s[j] - s[i-1];
        }
    }
    for (int i = n; i >= 1; i--){
        for (int j = i+1; j <= n; j++){
            if (i+1 <= j) c[i][j] = max(c[i][j], c[i+1][j]);
            if (j-1 >= i) c[i][j] = max(c[i][j], c[i][j-1]);
        }
    }
    for (int i = 1; i <= n; i++){
        for (int j = i; j <= n; j++){
            c[i][j] *= j - i + 1;
        }
    }

    memset(dp, 20, sizeof(dp));

    dp[0][0] = 0;
    for (int i = 1; i <= k; i++){
        for (int j = 0; j <= n; j++){
            for (int l = 0; l < j; l++){
                dp[i][j] = min(dp[i][j], dp[i-1][l] + c[l+1][j]);
            }
        }
    }
    // for (int i = 1; i <= k; i++){
    //     go(i, 1, n, 0, n);
    // }
    cout << dp[k][n] << "\n";

    // for (int i = 1; i <= n; i++){
    //     for (int j = i; j <= n; j++){
    //         dbg(i, j, c[i][j]);
    //     }
    // }
    // for (int i = 1; i <= k; i++){
    //     for (int j = 1; j <= n; j++){
    //         dbg(i, j, dp[i][j]);
    //     }
    // }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    solve();
    return 0;
} 