// BOJ 13263 나무 자르기

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

double cross(int i, int j, vector<pll> &v) { return (double)(v[j].se - v[i].se) / (v[i].fi - v[j].fi); }

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<int> b(n);
    for (int i = 0; i < n; i++)
        cin >> b[i];

    vector<pll> v = {make_pair(b[0], 0)};
    for (int i = 1; i < n; i++) {
        while (2 < v.sz && cross(v.sz - 2, v.sz - 1, v) <= cross(v.sz - 3, v.sz - 2, v))
            v.erase(v.end() - 2);

        int left = 0;
        int right = v.sz - 2;
        while (left <= right) {
            int mid = (left + right) / 2;

            if (cross(mid, mid + 1, v) <= a[i])
                left = mid + 1;
            else
                right = mid - 1;
        }

        v.push_back(make_pair(b[i], v[left].fi * a[i] + v[left].se));
    }

    cout << v.bk.se;
}

//--------------------------------------------------------------------------------

#include <bits/stdc++.h>
#define fi first
#define se second
#define sz size()
#define bk back()

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

ld cross(int i, int j, vector<pll> &v) {
    auto [x, y] = v[i];
    auto [z, w] = v[j];
    return (ld)(w - y) / (x - z);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<int> b(n);
    for (int i = 0; i < n; i++)
        cin >> b[i];

    vector<pll> v = {{b[0], 0}};
    int idx = 0;

    for (int i = 1; i < n; i++) {
        while (2 < v.sz && cross(v.sz - 2, v.sz - 1, v) <= cross(v.sz - 3, v.sz - 2, v))
            v.erase(v.end() - 2);

        while (idx + 1 < v.sz && cross(idx, idx + 1, v) <= a[i])
            idx++;

        v.push_back({b[i], v[idx].fi * a[i] + v[idx].se});
    }

    cout << v.bk.se;
}
