// BOJ 11401 이항 계수 3

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 4000005;
const int MOD = 1e9 + 7;
ll N, K, fac[MAX], inv[MAX];

ll ipow(ll base, ll exp) {
    ll ret = 1;
    while (exp) {
        if (exp & 1)
            ret = ret * base % MOD;
        exp >>= 1;
        base = base * base % MOD;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    fac[0] = 1;
    for (int i = 1; i < MAX; i++)
        fac[i] = fac[i - 1] * i % MOD;
    
    inv[MAX - 1] = ipow(fac[MAX - 1], MOD - 2);
    for (int i = MAX - 2; i >= 0; i--)
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    
    cin >> N >> K;
    cout << (fac[N] * inv[K] % MOD * inv[N - K] % MOD);
}
