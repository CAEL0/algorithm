// BOJ 11191 Xor Maximization

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

    vector<ll> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    vector<ll> basis;
    for (ll x : v) {
        for (ll y : basis)
            x = min(x, x ^ y);

        if (x)
            basis.push_back(x);
    }
    sort(basis.begin(), basis.end(), greater<>());

    ll ans = 0;
    for (ll x : basis)
        if (ans < (ans ^ x))
            ans ^= x;

    cout << ans;
}
