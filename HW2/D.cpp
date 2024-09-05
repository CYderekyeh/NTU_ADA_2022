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



int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    int n, m, mod;
    cin >> n >> m >> mod;
    auto add = [&](int &a, int b){
        a += b;
        if (a >= mod) a -= mod;
    };
    vector<vi> dp(2*m+1, vi(m+1)), ndp(dp), sdp(dp);
    auto reset = [&](){
        for (int i = 0; i <= 2*m; i++){
            for (int j = 0; j <= m; j++){
                ndp[i][j] = 0;
                sdp[i][j] = 0;
            }
        }
    };
    dp[0][0] = 1;
    for (int z = 0; z <= n; z++){
        for (int i = 0; i <= 2*m; i++){
            for (int j = 0; j <= m; j++){
                sdp[i][j] = dp[i][j];
                if (i && j){
                    add(sdp[i][j], sdp[i-1][j-1]);
                }
                add(ndp[i][j], sdp[i][j]);
            }
        }
        
        for (int i = 0; i <= 2*m; i++){
            for (int j = 0; j <= m; j++){
                add(ndp[i][j], mod - dp[i][j]);
                if (i && j + 1 <= m){
                    add(dp[i][j], dp[i-1][j+1]);
                }
                add(ndp[i][j], dp[i][j]);
            }
        }
        swap(dp, ndp);
        reset();
    }
    int ans = 0;
    for (int i = 0; i <= m; i++){
        add(ans, dp[2*i][0]);
    }
    cout << ans << "\n"; 
    return 0;
} 