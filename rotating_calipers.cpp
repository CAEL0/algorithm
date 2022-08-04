// BOJ 10254 고속도로

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int N;
struct Point {
    int x, y;
    bool operator<(const Point &o) const {
        return (x == o.x ? y < o.y : x < o.x);
    }
};
vector<Point> P, stk, stk_;

ll dist(Point a, Point b) {
    ll ret = 0;
    ret += pow((ll)(a.x - b.x), 2);
    ret += pow((ll)(a.y - b.y), 2);
    return ret;
}

ll ccw(Point a, Point b, Point c) {
    return (ll)(b.x - a.x) * (c.y - b.y) - (ll)(c.x - b.x) * (b.y - a.y);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T;
    cin >> T;
    while (T--) {
        cin >> N;

        stk.clear();
        stk_.clear();
        P.clear();
        P.resize(N);
        for (int i = 0; i < N; i++)
            cin >> P[i].x >> P[i].y;
        
        sort(P.begin(), P.end());

        stk.push_back(P[0]);
        stk.push_back(P[1]);
        for (int i = 2; i < N; i++) {
            while (stk.sz > 1 && ccw(stk[stk.sz - 2], stk.bk, P[i]) <= 0)
                stk.pop_back();
            stk.push_back(P[i]);
        }
        stk_.push_back(P[N - 1]);
        stk_.push_back(P[N - 2]);
        for (int i = N - 3; i >= 0; i--) {
            while (stk_.sz > 1 && ccw(stk_[stk_.sz - 2], stk_.bk, P[i]) <= 0)
                stk_.pop_back();
            stk_.push_back(P[i]);
        }
        for (int i = 1; i < stk_.sz - 1; i++)
            stk.push_back(stk_[i]);
        
        int m = stk.sz;
        int a = 0;
        int b = 0;
        for (int i = 1; i < m; i++)
            if (stk[i].x > stk[b].x)
                b = i;
        
        ll mx = dist(stk[a], stk[b]);
        int u = a;
        int v = b;
        for (int _ = 0; _ < 2 * m; _++) {
            int c = (a + 1) % m;
            int d = (b + 1) % m;
            if ((ll)(stk[c].x - stk[a].x) * (stk[b].y - stk[d].y) > (ll)(stk[b].x - stk[d].x) * (stk[c].y - stk[a].y))
                a = c;
            else
                b = d;
            
            ll res = dist(stk[a], stk[b]);
            if (mx < res) {
                mx = res;
                u = a;
                v = b;
            }
        }
        cout << stk[u].x << ' ' << stk[u].y << ' ' << stk[v].x << ' ' << stk[v].y << '\n';
    }
}
