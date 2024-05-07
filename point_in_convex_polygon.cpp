// BOJ 20670 미스테리 싸인

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

pll point_to_vector(pll &a, pll &b) { return {b.fi - a.fi, b.se - a.se}; }

ll ccw(pll &u, pll &v) { return u.fi * v.se - u.se * v.fi; }

bool is_inside(vector<pll> &points, pll &point) {
    pll left_vector = point_to_vector(points[0], points.bk);
    pll mid_vector = point_to_vector(points[0], point);
    pll right_vector = point_to_vector(points[0], points[1]);

    if (ccw(left_vector, mid_vector) >= 0)
        return false;

    if (ccw(right_vector, mid_vector) <= 0)
        return false;

    int left = 1;
    int right = points.sz - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        pll u = point_to_vector(points[0], points[mid]);

        if (ccw(u, mid_vector) > 0)
            left = mid + 1;
        else
            right = mid - 1;
    }

    pll v1 = point_to_vector(points[right], point);
    pll v2 = point_to_vector(point, points[right + 1]);

    return ccw(v1, v2) < 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    vector<pll> outer(n), inner(m);
    for (int i = 0; i < n; i++)
        cin >> outer[i].fi >> outer[i].se;

    for (int i = 0; i < m; i++)
        cin >> inner[i].fi >> inner[i].se;

    int ans = 0;
    
    for (int i = 0; i < k; i++) {
        ll x, y;
        cin >> x >> y;

        pll point = {x, y};
        if (!is_inside(outer, point) || is_inside(inner, point))
            ans++;
    }

    if (ans == 0)
        cout << "YES";
    else
        cout << ans;
}
