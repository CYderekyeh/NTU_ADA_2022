#include "choose.h"
#include <bits/stdc++.h>
using namespace std;

/*
Feel free to use global variables.
However, if you want to write your code more "correctly",
you can search for the keyword "anonymous namespace", a helpful tool in C++.
*/

void schedule(int n){
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j){
        int tmp = compare_task(i + 1, j + 1);
        if (tmp == 1){
            return true;
        }else{
            return false;
        }
    });
    int t1 = 0, t2 = 0;
    for (int i = 0; i < n; i++){
        int id = ord[i] + 1;
        if (t1 < t2){
            t1 = assign_task(1, id);
        }else{
            t2 = assign_task(2, id);
        }
    }
}
