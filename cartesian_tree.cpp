// BOJ 9798 Cartesian Tree

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<pair<pii, int>> v(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;

        v[i] = make_pair(make_pair(x, y), i + 1);
    }
    sort(v.begin(), v.end());

    vector<int> parent(n + 1);
    vector<int> left(n + 1);
    vector<int> right(n + 1);
    vector<int> stk;
    for (int i = 0; i < n; i++) {
        int j = -1;
        while (stk.sz && v[stk.bk].fi.se > v[i].fi.se) {
            j = stk.bk;
            stk.pop_back();
        }

        if (stk.sz) {
            parent[v[i].se] = v[stk.bk].se;
            right[v[stk.bk].se] = v[i].se;
        }

        if (j != -1) {
            parent[v[j].se] = v[i].se;
            left[v[i].se] = v[j].se;
        }

        stk.push_back(i);
    }

    cout << "YES" << '\n';
    for (int i = 1; i <= n; i++)
        cout << parent[i] << ' ' << left[i] << ' ' << right[i] << '\n';
}
