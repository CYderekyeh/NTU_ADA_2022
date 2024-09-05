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

    string s;
    ll m;
    cin >> s >> m;
    int n = s.size();
    
    auto Get = [&](char c){
        if ('0' <= c && c <= '9'){
            return c - '0';
        }else if ('A' <= c && c <= 'Z'){
            return c - 'A' + 10;
        }else{
            return c - 'a' + 36;
        }
    };
    int cnt = 62;
    vector<queue<int>> q(cnt); 
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        a[i] = Get(s[i]);
        q[a[i]].push(i);
    }

    vector<int> shift(cnt);
    vector<vector<int>> add(cnt, vector<int>(n));
    for (int i = 0; i < n; i++){
        bool found = false;
        for (int j = 0; j < cnt; j++){
            if (q[j].size() && q[j].front() + shift[j] - i <= m){

                int cost = q[j].front() + shift[j] - i;
                m -= cost;

                for (int k = j+1; k < cnt; k++){
                    if (q[k].size() && q[k].front() < q[j].front()){
                        shift[k]++;
                        add[k][q[j].front()]++;
                    }
                }
                int x = q[j].front();
                char c = s[x];
                q[j].pop();
                if (q[j].size()){
                    for (int k = x; k < q[j].front(); k++){
                        shift[j] -= add[j][k];
                    }
                }

                cout << c;
                found = true;
                break;
            }
        }
        assert(found);
    }

    return 0;
} 