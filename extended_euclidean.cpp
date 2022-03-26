// BOJ 14565 역원(Inverse) 구하기

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
    ll a0 = 1, a1 = 0, b0 = 0, b1 = 1, k;
    while (y) {
        k = x / y;
        swap(x, y);
        y %= x;
        swap(a0, a1);
        a1 -= k * a0;
        swap(b0, b1);
        b1 -= k * b0;
    }
    return pll(a0, b0);
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
