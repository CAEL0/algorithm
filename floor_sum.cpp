// BOJ 16998 It’s a Mod, Mod, Mod, Mod World

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

ll f(ll a, ll b, ll c, ll n) {
    ll ret = 0;

    while (1) {
        if (a >= c) {
            ret += n * (n + 1) / 2 * (a / c);
            a %= c;
        }

        if (b >= c) {
            ret += (n + 1) * (b / c);
            b %= c;
        }

        ll y_max = a * (n + 1) + b;
        if (y_max < c)
            break;

        n = y_max / c - 1;
        b = y_max % c;

        swap(c, a);
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        ll p, q, n;
        cin >> p >> q >> n;

        cout << p * n * (n + 1) / 2 - q * f(p, 0, q, n) << '\n';
    }
}
