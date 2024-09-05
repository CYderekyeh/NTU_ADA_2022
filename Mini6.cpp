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


void test_case(){
    srand(time(NULL));
    int n, m;
    cin >> n >> m;
    vector<vector<int>> cl(m, vector<int>(3));
    for (int i = 0; i < m; i++){
        cin >> cl[i][0] >> cl[i][1] >> cl[i][2];
    }
    vector<int> a(n);
    while (true){
        for (int i = 0; i < n; i++){
            a[i] = (rand() % 2 == 0 ? 1 : -1);
        }
        int cnt = 0;
        for (int i = 0; i < m; i++){
            bool ok = false;
            for (int j = 0; j < 3; j++){
                if (cl[i][j] > 0){
                    if (a[cl[i][j]-1] == 1){
                        ok = true;
                        break;
                    }
                }else{
                    if (a[-cl[i][j]-1] == -1){
                        ok = true;
                        break;
                    }
                }
                
            }
            cnt += ok;
        }
        if (cnt * 8 >= 7 * m){
            break;
        }
    }
    for (int i = 0; i < n; i++){
        cout << a[i] << " \n"[i==n-1];
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    int t = 1;
    // cin >> t;
    while(t--){
        test_case();
    }
    return 0;
} 