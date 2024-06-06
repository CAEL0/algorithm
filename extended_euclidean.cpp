// BOJ 14565 역원(Inverse) 구하기

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

pll extended_gcd(ll x, ll y) {
    ll a0 = 1, a1 = 0, b0 = 0, b1 = 1, k, yy = y;
    
    while (y) {
        k = x / y;
        swap(x, y);
        y %= x;
        swap(a0, a1);
        a1 -= k * a0;
        swap(b0, b1);
        b1 -= k * b0;
    }
    
    if (a0 < 0)
        a0 += yy;
    
    return pll(a0, b0);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll n, a;
    cin >> n >> a;

    if (gcd(n, a) != 1)
        cout << n - a << ' ' << -1;
    else
        cout << n - a << ' ' << extended_gcd(a, n).fi;
}
