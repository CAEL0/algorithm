// BOJ 4149 큰 수 소인수분해

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

random_device rd;
mt19937_64 mt(rd());
uniform_int_distribution<ll> dist;

ll get_random(ll a, ll b) { return dist(mt) % (b - a + 1) + a; }

ll ipow(ll base, ll exp, ll mod) {
    ll ret = 1;
    base %= mod;

    while (exp) {
        if (exp & 1)
            ret = (__int128)ret * base % mod;

        exp >>= 1;
        base = (__int128)base * base % mod;
    }

    return ret;
}

bool miller_rabin(ll x) {
    if (x == 1)
        return false;

    int s = 0;
    ll d = x - 1;

    while (!(d & 1)) {
        s++;
        d >>= 1;
    }

    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (a >= x - 1)
            break;

        ll b = ipow(a, d, x);
        if (b == 1 || b == x - 1)
            continue;

        if (s == 1)
            return false;

        bool flag = true;
        for (int i = 0; i < s - 1; i++) {
            b = (__int128)b * b % x;

            if (b == x - 1) {
                flag = false;
                break;
            }
        }

        if (flag)
            return false;
    }
    return true;
}

void pollard_rho(ll x, vector<ll> &factors, ll n) {
    if (x == 1)
        return;

    if (x % 2 == 0) {
        factors.push_back(2);
        pollard_rho(x / 2, factors, n);
        return;
    }

    if (miller_rabin(x)) {
        factors.push_back(x);
        return;
    }

    while (1) {
        ll c = get_random(1, n - 1);
        ll t = 1;
        ll r = 1;
        ll g = 1;
        bool flag = true;

        while (g == 1) {
            t = (ipow(t, 2, x) + c) % x;
            r = ((((__int128)2 * c % x * ipow(r, 2, x) % x + ipow(r, 4, x)) % x + ipow(c, 2, x)) % x + c) % x;
            g = gcd(abs(t - r), x);

            if (g == n) {
                flag = false;
                break;
            }
        }

        if (flag) {
            pollard_rho(g, factors, n);
            pollard_rho(x / g, factors, n);
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll n;
    cin >> n;

    vector<ll> factors;
    pollard_rho(n, factors, n);

    sort(factors.begin(), factors.end());

    for (ll p : factors)
        cout << p << '\n';
}
