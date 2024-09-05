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

#define FOR(i, a, b) for (int i=a; i<(b); i++)
#define F0R(i, a) for (int i=0; i<(a); i++)
#define FORd(i,a,b) for (int i = (b)-1; i >= a; i--)
#define F0Rd(i,a) for (int i = (a)-1; i >= 0; i--)
#define trav(a,x) for (auto& a : x)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

#define vt vector
#define ar array
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
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

template <typename T>
class fenwick {
 public:
  vector<T> fenw;
  int n;
 
  fenwick(int _n) : n(_n) {
    fenw.resize(n);
  }
 
  void modify(int x, T v) {
    while (x < n) {
      fenw[x] += v;
      x |= (x + 1);
    }
  }
 
  T get(int x) {
    T v{};
    while (x >= 0) {
      v += fenw[x];
      x = (x & (x + 1)) - 1;
    }
    return v;
  }
};

void solve(){
    int n;
    cin >> n;
    ll l1, l2, r1, r2;
    cin >> l1 >> l2 >> r1 >> r2;
    vector<ll> x(n), y(n);
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++){
        cin >> x[i] >> y[i];
        v.emplace_back(x[i], y[i]);
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++){
        tie(x[i], y[i]) = v[i];
    }

    auto comp = [&](vector<ll> &a){
        vector<ll> vals(a);
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        for (int i = 0; i < n; i++){
            a[i] = lower_bound(vals.begin(), vals.end(), a[i]) - vals.begin() + 1;
        }
    };
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++){
        a[i] = l2 * y[i] - l1 * x[i];
        b[i] = r2 * y[i] - r1 * x[i];
    }

    comp(a);
    comp(b);

    ll ans = (ll) n * (n-1) / 2;
    fenwick<int> bit1(n+1), bit2(n+1);
    int beg = 0;
    while (beg < n){
        int end = beg;
        while (end + 1 < n && x[end+1] == x[end]){
            end++;
        }
        for (int i = beg; i <= end; i++){
            ans -= beg - bit1.get(a[i]);
            ans -= bit2.get(b[i]-1);
        }
        for (int i = beg; i <= end; i++){
            bit1.modify(a[i], 1);
            bit2.modify(b[i], 1);
        }
        int len = end - beg + 1;
        ans -= (ll) len * (len-1) / 2;
        beg = end + 1;
    }
    cout << ans << '\n';
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
    return 0;
} 