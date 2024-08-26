// BOJ 8986 전봇대

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

ll f(ll k, vector<int> &v) {
    ll ret = 0;
    ll x = k;

    for (int i = 1; i < v.sz; i++) {
        ret += abs(v[i] - x);
        x += k;
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    ll left = 0;
    ll right = v[n - 1];

    while (left + 3 <= right) {
        ll p = (right + 2 * left) / 3;
        ll q = (left + 2 * right) / 3;

        if (f(p, v) >= f(q, v))
            left = p;
        else
            right = q;
    }

    ll ans = f(left, v);
    for (int x = left + 1; x <= right; x++)
        ans = min(ans, f(x, v));

    cout << ans;
}
