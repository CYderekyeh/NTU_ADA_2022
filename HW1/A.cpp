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



int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    int n;
    cin >> n;
    vector<int> res, res2;
    vector<int> a;
    auto Place = [&](int x){
        a.push_back(x);
        res.push_back(1);
        res2.push_back(x);
    };
    auto Pop = [&](){
        int x = a.back();
        a.pop_back();
        res.push_back(2);
        return x;
    };
    auto Photo = [&](){
        res.push_back(3);
    };
    for (int i = n; i >= 1; i--){
        Place(i);
    }
    function<void(int, int)> dc = [&](int l, int r){
        if (l == r){
            Photo();
            return;
        }
        int m = (l + r) >> 1;
        dc(l, m);
        vector<int> L, R;
        for (int i = l; i <= m; i++) L.push_back(Pop());
        for (int i = m+1; i <= r; i++) R.push_back(Pop());
        while (L.size()){
            Place(L.back());
            L.pop_back();
        }
        while (R.size()){
            Place(R.back());
            R.pop_back();
        }
        dc(m+1, r);
    };
    dc(1, n);
    cout << res.size() << '\n';
    int i = 0;
    for (auto t:res){
        if (t == 1){
            cout << "PLACE " << res2[i++] << '\n';
        }else if (t == 2){
            cout << "POP\n"; 
        }else{
            cout << "PHOTO\n";
        }
    }
    return 0;
} 