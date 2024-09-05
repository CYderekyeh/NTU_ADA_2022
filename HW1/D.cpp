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

const int maxn = 5e5 + 5;
const int maxm = 2e5 + 5;
int n, a[maxn];
int cnt[maxm], cnt2[maxm];
int f[maxn];
ll ans = 0;

template <typename T>
inline bool read(T& x) {
  char c = 0; bool flag = false;
  while (c = getchar(), (c < '0' && c != '-') || c > '9') if (c == -1) return false;
  c == '-' ? (flag = true, x = 0) : (x = c - '0');
  while (c = getchar(), c >= '0' && c <= '9') x = x * 10 + c - '0';
  if (flag) x = -x;
  return true;
}



void dc(int l, int r){
    if (l == r) return;
    int m = (l + r) >> 1;
    dc(l, m);
    dc(m+1, r);
    

    f[m] = a[m];
    for (int i = m-1; i >= l; i--){
        f[i] = min(f[i+1], a[i]);
    }
    for (int i = l; i <= m; i++){
        cnt2[a[i]]++;
    }

    int mn = a[m+1];
    int j = l;
    while (j <= m && f[j] <= mn){
        cnt[a[j] + f[j]]++;
        if (a[j] - f[j] >= 0) cnt[a[j] - f[j]]++;
        cnt2[a[j]]--;
        j++;
    }
    for (int i = m+1 ; i <= r; i++){
        ckmin(mn, a[i]);
        while (j-1 >= l && f[j-1] > mn){
            j--;
            cnt[a[j] + f[j]]--;
            if (a[j] - f[j] >= 0) cnt[a[j] - f[j]]--;
            cnt2[a[j]]++;
        }
        // min at left
        ans += cnt[a[i]];

        // min at right
        if (a[i] + mn < maxm) ans += cnt2[a[i] + mn];
        if (a[i] - mn >= 0) ans += cnt2[a[i] - mn];

        if (i == r){
            int k = j;
            while (k <= m) cnt2[a[k++]]--;
            while (j-1 >= l){
                j--;
                cnt[a[j] + f[j]]--;
                if (a[j] - f[j] >= 0) cnt[a[j] - f[j]]--;
            }
        }
    }
}



int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    read(n);
    for (int i = 1; i <= n; i++) read(a[i]);
    dc(1, n);
    cout << ans << '\n';
    return 0;
} 