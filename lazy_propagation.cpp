// BOJ 10999 구간 합 구하기 2

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 3000005;
int N, M, K;
ll tree[MAX], lazy[MAX];

ll init(int idx, int s, int e) {
    if (s == e) {
        cin >> tree[idx];
        return tree[idx];
    }
    int m = (s + e) >> 1;
    return tree[idx] = init(2 * idx, s, m) + init(2 * idx + 1, m + 1, e);
}
void propagate(int idx, int s, int e) {
    if (lazy[idx]) {
        if (s != e) {
            lazy[2 * idx] += lazy[idx];
            lazy[2 * idx + 1] += lazy[idx];
        }
        tree[idx] += (e - s + 1) * lazy[idx];
        lazy[idx] = 0;
    }
}
ll summation(int idx, int s, int e, int l, int r) {
    propagate(idx, s, e);
    if (r < s || e < l)
        return 0;
    
    if (l <= s && e <= r)
        return tree[idx];
    
    int m = (s + e) >> 1;
    return summation(2 * idx, s, m, l, r) + summation(2 * idx + 1, m + 1, e, l, r);
}
void update(int idx, int s, int e, int l, int r, ll v) {
    propagate(idx, s, e);
    if (r < s || e < l)
        return;
    
    if (l <= s && e <= r) {
        lazy[idx] = v;
        propagate(idx, s, e);
        return;
    }
    int m = (s + e) >> 1;
    update(2 * idx, s, m, l, r, v);
    update(2 * idx + 1, m + 1, e, l, r, v);
    tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M >> K;

    init(1, 1, N);
    
    for (int i = 0; i < M + K; i++) {
        int a;
        cin >> a;
        if (a == 1) {
            int b, c;
            ll d;
            cin >> b >> c >> d;
            update(1, 1, N, b, c, d);
        } else {
            int b, c;
            cin >> b >> c;
            cout << summation(1, 1, N, b, c) << '\n';
        }
    }
}
