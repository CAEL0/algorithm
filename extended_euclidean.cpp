// BOJ 14565

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

ll gcd(ll x, ll y) {
    while (x % y) {
        swap(x, y);
        y %= x;
    }
    return y;
}
pll extended_gcd(ll x, ll y) {
    ll x0 = 1, x1 = 0, y0 = 0, y1 = 1, k;
    while (y) {
        k = x / y;
        swap(x, y);
        y %= x;
        swap(x0, x1);
        x1 -= k * x0;
        swap(y0, y1);
        y1 -= k * y0;

    }
    return pll(x0, y0);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll n, a;
    cin >> n >> a;
    
    if (gcd(n, a) != 1)
        cout << n - a << ' ' << -1;
    else {
        ll c, d;
        tie(c, d) = extended_gcd(n, a);
        if (d < 0)
            cout << n - a << ' ' << n + d;
        else
            cout << n - a << ' ' << d;
    }
}
