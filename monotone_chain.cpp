// BOJ 1708 볼록 껍질

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll ccw(pll p, pll q, pll r) { return (q.fi - p.fi) * (r.se - q.se) - (r.fi - q.fi) * (q.se - p.se); }

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<pll> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i].fi >> v[i].se;

    sort(v.begin(), v.end());

    vector<pll> stk1 = {v[0], v[1]};
    for (int i = 2; i < n; i++) {
        while (stk1.sz > 1 && ccw(stk1[stk1.sz - 2], stk1.bk, v[i]) <= 0)
            stk1.pop_back();

        stk1.push_back(v[i]);
    }

    vector<pll> stk2 = {v.bk, v[v.sz - 2]};
    for (int i = n - 3; i >= 0; i--) {
        while (stk2.sz > 1 && ccw(stk2[stk2.sz - 2], stk2.bk, v[i]) <= 0)
            stk2.pop_back();

        stk2.push_back(v[i]);
    }

    for (int i = 1; i < stk2.sz - 1; i++)
        stk1.push_back(stk2[i]);

    cout << stk1.sz;
}
