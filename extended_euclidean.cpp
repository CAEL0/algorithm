// BOJ 14565

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

pll extended_gcd(ll x, ll y) {
    ll x0 = 1, y1 = 1, x1 = 0, y0 = 0, n, tmp;
    while (y) {
        n = x / y;
        tmp = x;
        x = y;
        y = tmp % y;
        tmp = x0;
        x0 = x1;
        x1 = tmp - n * x1;
        tmp = y0;
        y0 = y1;
        y1 = tmp - n * y1;
    }
    return pll(x0, y0);
}
