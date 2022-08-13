// BOJ 16975 수열과 쿼리 21

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 100005;
int N, Q, A[MAX];
ll tree[4 * MAX];

void range(int idx, int s, int e, int l, int r, ll v) {
    if (r < s || e < l)
        return;
    
    if (l <= s && e <= r) {
        tree[idx] += v;
        return;
    }
    int m = (s + e) >> 1;
    range(2 * idx, s, m, l, r, v);
    range(2 * idx + 1, m + 1, e, l, r, v);
}
ll point(int idx, int s, int e, int l) {
    if (l < s || e < l)
        return 0;
    
    if (s == e)
        return tree[idx];
    
    int m = (s + e) >> 1;
    return tree[idx] + point(2 * idx, s, m, l) + point(2 * idx + 1, m + 1, e, l);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> A[i];
    
    cin >> Q;
    while (Q--) {
        int q;
        cin >> q;
        if (q == 1) {
            int i, j, k;
            cin >> i >> j >> k;
            range(1, 1, N, i, j, k);
        } else {
            int x;
            cin >> x;
            cout << point(1, 1, N, x) + A[x] << '\n';
        }
    }
}