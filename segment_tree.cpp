//BOJ 2042 구간 합 구하기

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int powh;
ll tree[3000010];

ll add(int a, int b) {
    ll res = 0;
    a += powh - 1;
    b += powh - 1;
    while (a <= b) {
        if (a % 2)
            res += tree[a++];
        if (b % 2 == 0)
            res += tree[b--];
        a /= 2;
        b /= 2;
    }
    return res;
}
void update(int k, ll c) {
    int idx = powh + k - 1;
    ll gap = tree[idx] - c;
    while (idx >= 1) {
        tree[idx] -= gap;
        idx /= 2;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, x, y;
    cin >> n >> x >> y;

    int height = ceil(log2(n));
    powh = pow(2, height);

    for (int i = 0; i < n; i++)
        cin >> tree[powh + i];
    
    for (int h = height - 1; h >= 0; h--)
        for (int i = pow(2, h); i < pow(2, h + 1); i++)
            tree[i] = tree[2 * i] + tree[2 * i + 1];
    
    for (int i = 0; i < x + y; i++) {
        ll p, q, r;
        cin >> p >> q >> r;
        if (p == 1)
            update(q, r);
        else
            cout << add(q, r) << '\n';
    }
}
