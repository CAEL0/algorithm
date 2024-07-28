// BOJ 11001 김치

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

ll f(int i, int j, vector<ll> &t, vector<ll> &v) { return t[j] * (j - i) + v[i]; }

void g(int s, int e, int l, int r, vector<ll> &t, vector<ll> &v, int d, ll &ans) {
    if (s > e)
        return;

    int i = (s + e) >> 1;
    int k = i;
    for (int j = max(i + 1, l); j <= min(i + d, r); j++)
        if (f(i, k, t, v) < f(i, j, t, v))
            k = j;

    ans = max(ans, f(i, k, t, v));

    g(s, i - 1, l, k, t, v, d, ans);
    g(i + 1, e, k, r, t, v, d, ans);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, d;
    cin >> n >> d;

    vector<ll> t(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> t[i];

    vector<ll> v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    ll ans = 0;

    g(1, n, 1, n, t, v, d, ans);

    cout << ans;
}
