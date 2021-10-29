#include <iostream>
#include <bits/stdc++.h>
#define fi first
#define se second
#define sz size()

using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

int n, x, y;

int f(pii u) {
    if (u.fi > x) return 0;
    if (u.fi < x) return 2;
    return 1;
}
bool cmp1(pii u, pii v) {
    return u.se == v.se ? u.fi < v.fi: u.se < v.se;
}
bool cmp2(pii u, pii v) {
    if (f(u) != f(v)) return f(u) < f(v);
    if (f(u) == 1) return u.se < v.se;
    double tanu = (double)(u.se - y) / (u.fi - x);
    double tanv = (double)(v.se - y) / (v.fi - x);
    return tanu == tanv ? u.fi < v.fi: tanu < tanv;
}
ll ccw(pii u, pii v, pii w) {
    return (ll)(v.fi - u.fi) * (w.se - v.se) - (ll)(w.fi - v.fi) * (v.se - u.se);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    pii arr[n];
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        arr[i] = pii(x, y);
    }
    sort(arr, arr + n, cmp1);
    x = arr[0].fi;
    y = arr[0].se;
    sort(arr + 1, arr + n, cmp2);
    
    vector<pii> stk;
    stk.push_back(arr[0]);
    stk.push_back(arr[1]);
    
    for (int i = 2; i < n; i++) {
        while (stk.sz > 1) {
            if (ccw(stk[stk.sz - 2], stk[stk.sz - 1], arr[i]) <= 0)
                stk.pop_back();
            else
                break;
        }
        stk.push_back(arr[i]);
    }
    if (stk.sz > 2 && ccw(stk[stk.sz - 2], stk[stk.sz - 1], stk[0]) <= 0)
        stk.pop_back();
    cout << stk.sz;
}
