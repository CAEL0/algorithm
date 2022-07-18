#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll ipow(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while (exp) {
        if (exp & 1)
            res = res * base % mod;
        exp >>= 1;
        base = base * base % mod;
    }
    return res;
}
bool miller_rabin(ll x) {
    if (x == 1)
        return false;
    
    ll s = 0;
    ll d = x - 1;
    while (!(d & 1)) {
        s++;
        d >>= 1;
    }
    for (ll a: {2, 7, 61}) {
        if (a >= x - 1)
            break;
        
        ll b = ipow(a, d, x);
        if (b == 1 || b == x - 1)
            continue;
        
        if (s == 1)
            return false;
        
        bool flag = true;
        for (int i = 0; i < s - 1; i++) {
            b = b * b % x;
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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int x;
    cin >> x;

    bool ans;
    ans = miller_rabin(x);
    
    cout << ans;
}
