// BOJ 17474 수열과 쿼리 26

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 1000005;
int N, Q, A[MAX];

struct Node {
    ll mx1, mx2, mxcnt, total;
} tree[4 * MAX];

Node merge(Node a, Node b) {
    if (a.mx1 == b.mx1)
        return {a.mx1, max(a.mx2, b.mx2), a.mxcnt + b.mxcnt, a.total + b.total};
    
    if (a.mx1 > b.mx1)
        swap(a, b);
    return {b.mx1, max(a.mx1, b.mx2), b.mxcnt, a.total + b.total};
}
Node init(int idx, int s, int e) {
    if (s == e)
        return tree[idx] = {A[s], -1, 1, A[s]};
    
    int m = (s + e) >> 1;
    return tree[idx] = merge(init(2 * idx, s, m), init(2 * idx + 1, m + 1, e));
}
void propagate(int idx, int s, int e) {
    if (s != e) {
        for (int i: {2 * idx, 2 * idx + 1}) {
            if (tree[idx].mx1 < tree[i].mx1) {
                tree[i].total += tree[i].mxcnt * (tree[idx].mx1 - tree[i].mx1);
                tree[i].mx1 = tree[idx].mx1;
            }
        }
    }
}
void update(int idx, int s, int e, int l, int r, int v) {
    propagate(idx, s, e);
    if (r < s || e < l || tree[idx].mx1 <= v)
        return;
    
    if (l <= s && e <= r && tree[idx].mx2 < v) {
        tree[idx].total += tree[idx].mxcnt * (v - tree[idx].mx1);
        tree[idx].mx1 = v;
        propagate(idx, s, e);
        return;
    }
    int m = (s + e) >> 1;
    update(2 * idx, s, m, l, r, v);
    update(2 * idx + 1, m + 1, e, l, r, v);
    tree[idx] = merge(tree[2 * idx], tree[2 * idx + 1]);
}
int maximum(int idx, int s, int e, int l, int r) {
    propagate(idx, s, e);
    if (r < s || e < l)
        return 0;
    
    if (l <= s && e <= r)
        return tree[idx].mx1;
    
    int m = (s + e) >> 1;
    return max(maximum(2 * idx, s, m, l, r), maximum(2 * idx + 1, m + 1, e, l, r));
}
ll summation(int idx, int s, int e, int l, int r) {
    propagate(idx, s, e);
    if (r < s || e < l)
        return 0;
    
    if (l <= s && e <= r)
        return tree[idx].total;
    
    int m = (s + e) >> 1;
    return summation(2 * idx, s, m, l, r) + summation(2 * idx + 1, m + 1, e, l, r);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> A[i];
    
    init(1, 1, N);
    cin >> Q;
    while (Q--) {
        int q, l, r;
        cin >> q >> l >> r;
        if (q == 1) {
            int v;
            cin >> v;
            update(1, 1, N, l, r, v);
        } else if (q == 2)
            cout << maximum(1, 1, N, l, r) << '\n';
        else
            cout << summation(1, 1, N, l, r) << '\n';
    }
}
