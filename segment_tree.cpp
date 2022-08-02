//BOJ 2042 구간 합 구하기

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int N, M, K;
ll tree[3000010];

ll init(int idx, int s, int e) {
    if (s == e) {
        cin >> tree[idx];
        return tree[idx];
    }
    int m = (s + e) >> 1;
    return tree[idx] = init(2 * idx, s, m) + init(2 * idx + 1, m + 1, e);
}
ll summation(int idx, int s, int e, int l, int r) {
    if (l < s || e < l)
        return 0;
    
    if (l <= s && e <= r)
        return tree[idx];
    
    int m = (s + e) >> 1;
    return summation(2 * idx, s, m, l, r) + summation(2 * idx + 1, m + 1, e, l, r);
}
void update(int idx, int s, int e, int l, ll v) {
    if (r < s || e < l)
        return;
    
    if (s == e) {
        tree[idx] = v;
        return;
    }
    int m = (s + e) >> 1;
    update(2 * idx, s, m, l, v);
    update(2 * idx + 1, m + 1, e, l, v);
    tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M >> K;

    init(1, 1, N);
    
    for (int i = 0; i < M + K; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        if (a == 1)
            update(1, 1, N, b, c);
        else
            cout << summation(1, 1, N, b, c) << '\n';
    }
}

//--------------------------------------------------------------------------------

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int powh;
ll tree[3000010];

ll summation(int a, int b) {
    ll res = 0;
    a += powh - 1;
    b += powh - 1;
    while (a <= b) {
        if (a & 1)
            res += tree[a++];
        if (!(b & 1))
            res += tree[b--];
        a >>= 1;
        b >>= 1;
    }
    return res;
}
void update(int k, ll c) {
    int idx = powh + k - 1;
    ll gap = tree[idx] - c;
    while (idx) {
        tree[idx] -= gap;
        idx >>= 1;
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
