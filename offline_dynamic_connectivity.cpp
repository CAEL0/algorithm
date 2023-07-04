// BOJ 16911 그래프와 쿼리

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 100005;
int dsu[MAX], rnk[MAX], convert[MAX], ans[MAX];
vector<pii> tree[4 * MAX];
vector<pair<pii, int>> stk;

struct Query {
    int op, x, y;
} query[MAX];

void update(int idx, int s, int e, int l, int r, int x, int y) {
    if (r < s || e < l)
        return;

    if (l <= s && e <= r) {
        tree[idx].push_back({x, y});
        return;
    }
    int m = (s + e) >> 1;
    update(2 * idx, s, m, l, r, x, y);
    update(2 * idx + 1, m + 1, e, l, r, x, y);
}

int find(int z) {
    if (z == dsu[z])
        return z;
    return find(dsu[z]);
}

int uni(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y)
        return 0;

    if (rnk[x] < rnk[y])
        swap(x, y);

    dsu[y] = x;
    if (rnk[x] == rnk[y]) {
        rnk[x]++;
        stk.push_back({{x, y}, 1});
    } else
        stk.push_back({{x, y}, 0});
    return 1;
}

void rollback(int cnt) {
    while (cnt--) {
        auto [p, k] = stk.bk;
        stk.pop_back();

        dsu[p.se] = p.se;
        if (k)
            rnk[p.fi]--;
    }
}

void solve(int idx, int s, int e) {
    int cnt = 0;
    for (pii &p : tree[idx])
        cnt += uni(p.fi, p.se);

    if (s == e) {
        ans[s] = (find(query[convert[s]].x) == find(query[convert[s]].y));
        rollback(cnt);
        return;
    }
    int m = (s + e) >> 1;
    solve(2 * idx, s, m);
    solve(2 * idx + 1, m + 1, e);
    rollback(cnt);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        dsu[i] = i;
        rnk[i] = 1;
    }
    int k = 0;
    for (int i = 0; i < q; i++) {
        int op, x, y;
        cin >> op >> x >> y;
        if (x > y)
            swap(x, y);

        query[i] = {op, x, y};
        if (op == 3)
            convert[++k] = i;
    }
    int t = 1;
    map<pii, int> mp;
    for (int i = 0; i < q; i++) {
        auto [op, x, y] = query[i];
        if (op == 1)
            mp[{x, y}] = t;
        else if (op == 2) {
            update(1, 1, k, mp[{x, y}], t - 1, x, y);
            mp.erase({x, y});
        } else if (op == 3)
            t++;
    }
    for (auto it = mp.begin(); it != mp.end(); it++)
        update(1, 1, k, it->se, t, it->fi.fi, it->fi.se);

    solve(1, 1, k);
    for (int i = 1; i <= k; i++)
        cout << ans[i] << '\n';
}
