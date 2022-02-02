// BOJ 2042

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n;
ll tree[2000010];

ll summation(int k) {
    ll res = 0;
    while (k > 0) {
        res += tree[k];
        k -= (k & -k);
    }
    return res;
}
void update(int k, ll c) {
    while (k < 2 * n) {
        tree[k] += c;
        k += (k & -k);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int m, k;
    cin >> n >> m >> k;

    for (ll tmp, i = 1; i <= n; i++) {
        cin >> tmp;
        update(i, tmp);
    }
    ll a, b, c;
    for (int i = 0; i < m + k; i++) {
        cin >> a >> b >> c;
        if (a == 1) {
            ll tmp = summation(b) - summation(b - 1);
            update(b, c - tmp);
        }
        else cout << summation(c) - summation(b - 1) << '\n';
    }
}
