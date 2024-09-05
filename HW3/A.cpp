#include<bits/stdc++.h>
using namespace std;
#define spIO ios::sync_with_stdio(false);cin.tie(0)
typedef long long ll;
typedef long double ld;
#define DBG(x) cout<<(#x " = ")<<x<<endl;
#define ALL(x) x.begin(),x.end()


template <typename T>
inline bool read(T& x) {
  char c = 0; bool flag = false;
  while (c = getchar(), (c < '0' && c != '-') || c > '9') if (c == -1) return false;
  c == '-' ? (flag = true, x = 0) : (x = c - '0');
  while (c = getchar(), c >= '0' && c <= '9') x = x * 10 + c - '0';
  if (flag) x = -x;
  return true;
}

int main(){
    spIO;
    int m;
    read(m);
    vector<ll> v, pref(1, 0);
    ll sum = 0;
    int n = 0;
    for (int i = 0; i < m; i++){
        string s;
        char c = 0;
        while (c = getchar(), ('A' <= c && c <= 'Z')){
            s.push_back(c);
        }
        if (s[0] == 'P'){
            int w;
            read(w);
            n++;
            v.push_back(w);
            pref.push_back(pref.back() + w);
            sum += w;
        }else if (s[0] == 'T'){
            int w = v.back();
            n--;
            v.pop_back();
            pref.pop_back();
            sum -= w;
            cout << w << "\n";
        }else if (s[0] == 'C'){
            int x, k;
            read(x);
            read(k);
            vector<int> tmp;
            for (int j = 0; j < x; j++){
                int w = v.back();
                v.pop_back();
                pref.pop_back();
                tmp.push_back(w);
            }
            ll take = 0;
            vector<int> ord(tmp);
            sort(ALL(ord));
            for (int j = 0; j < (x + k - 1) / k; j++){
                int w = ord.back();
                ord.pop_back();
                take += w;
            }
            while(tmp.size()){
                int w = tmp.back();
                tmp.pop_back();
                if (w <= ord.back()){
                    v.push_back(w);
                    pref.push_back(pref.back() + w);
                }
            }
            n -= (x + k - 1) / k;
            sum -= take;
            cout << take << "\n";

        }else if (s[0] == 'D'){
            int x;
            read(x);
            assert(x <= n);
            cout << sum - pref[n - x] << "\n";
        }
    }
    return 0;
}



