#include <bits/stdc++.h>
using namespace std;


struct Heap{
    int id;
    long long freq;
    Heap *left, *right;
    Heap(int _id, int _freq){
        left = right = NULL;
        id = _id;
        freq = _freq;
    }
};

struct cmp{
    bool operator()(Heap *x, Heap *y){
        return x->freq > y->freq;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    if (n == 1){
        cout << "0\n";
        return 0;
    }
    // vector<int> ord(n);
    // iota(ord.begin(), ord.end(), 0);
    // sort(ord.begin(), ord.end(), [&](int i, int j){
    //     return a[i] < a[j];
    // });
    priority_queue<Heap*, vector<Heap*>, cmp> pq;
    for (int i = 0; i < n; i++){
        pq.push(new Heap(i, a[i]));
    }
    while (pq.size() > 1){
        Heap *x = pq.top();
        pq.pop();
        Heap *y = pq.top();
        pq.pop();
        
        Heap *z = new Heap(n, x->freq + y->freq);
        pq.push(z);
        z->left = x;
        z->right = y;
    }

    vector<string> res(n);
    string cur = "";
    function<void(Heap*)> dfs = [&](Heap *it){
        if (it->id < n){
            res[it->id] = cur;
        }
        if (it->left){
            cur.push_back('0');
            dfs(it->left);
            cur.pop_back();
            cur.push_back('1');
            dfs(it->right);
            cur.pop_back();
        }
    };
    dfs(pq.top());
    for (int i = 0; i < n; i++){
        cout << res[i] << "\n";
    }
}