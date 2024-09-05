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



const ll inf = 2e18;
struct Edge{
    int to;
    ll w, c;
    Edge (int x, ll y, ll z) : to(x), w(y), c(z) {}
    bool operator < (Edge const& other) const {
        if (w != other.w) return w < other.w;
        else if (c != other.c) return c < other.c;
        else return to < other.to;
    }
};


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);     
    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> adj(n);
    for (int i = 0; i < m; i++){
        int u, v, w, c;
        cin >> u >> v >> w >> c;
        adj[u].emplace_back(v, w, c);
        adj[v].emplace_back(u, w, c);
    }

    ll ans = 0;
    vector<ll> max_len(n), res(n);
    vector<ll> par(n, -1), minw(n, inf), minc(n, inf);
    par[0] = minw[0] = minc[0] = 0;
    set<Edge> q;
    q.emplace(0, 0, 0);
    vector<bool> vis(n, false);
	for (int i = 0; i < n; i++) {
        assert(q.size());

		int u = q.begin()->to;
		vis[u] = true;
		res[u] = q.begin()->c;
		max_len[u] = max(max_len[par[u]], q.begin()->w);
		ans += q.begin()->c;
		q.erase(q.begin());
        // dbg(u, max_len[u], res[u]);

		for (auto [v, w, c] :adj[u]){
            if (w == max_len[u]){
                c += res[u];
            }else if (w < max_len[u]){
                c = res[u];
            }
            // dbg(v, w, c, minw[v], minc[v]);
			if(!vis[v] && (w < minw[v] || (w == minw[v] && c < minc[v])) ) {
                auto it = q.find({v, minw[v], minc[v]});

				if (it != q.end()) q.erase(it);
                par[v] = u;
                minw[v] = w;
                minc[v] = c;
                // dbg(v, w, c);
				q.emplace(v, w, c);
                
			}
		}
	}
    cout << ans << "\n";
    return 0;
}
