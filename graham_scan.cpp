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

ll ccw(pll &u, pll &v, pll &w) { return (v.fi - u.fi) * (w.se - v.se) - (w.fi - v.fi) * (v.se - u.se); }

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<pll> points(n);
    for (int i = 0; i < n; i++)
        cin >> points[i].fi >> points[i].se;

    sort(points.begin(), points.end(), [](pll &p, pll &q) {
        if (p.se == q.se)
            return p.fi > q.fi;
        return p.se < q.se;
    });

    sort(points.begin() + 1, points.end(), [&](pll &p, pll &q) {
        ll k = ccw(points[0], p, q);

        if (k)
            return k > 0;

        if (p.se == q.se)
            return p.fi < q.fi;
        return p.se < q.se;
    });

    vector<pll> v = {points[0], points[1]};

    for (int i = 2; i < n; i++) {
        while (v.sz >= 2 && ccw(v[v.sz - 2], v.bk, points[i]) <= 0)
            v.pop_back();

        v.push_back(points[i]);
    }

    if (v.sz >= 3 && ccw(v[v.sz - 2], v.bk, v[0]) <= 0)
        v.pop_back();

    cout << v.sz;
}
