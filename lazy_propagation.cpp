// BOJ 10999 구간 합 구하기 2

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int N, M, K;
ll tree[3000010], lazy[3000010];

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
        if (s != e) {
            lazy[2 * idx] += v;
            lazy[2 * idx + 1] += v;
        }
        tree[idx] += (e - s + 1) * v;
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

//--------------------------------------------------------------------------------

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int N, M, K;
ll powh;

struct Node {
    ll val, lazy;
} tree[4000010];

struct Range {
    int l, r, idx;
};

ll summation(int l, int r) {
    ll res = 0;
    stack<Range> stk;
    stk.push({l, r, 1});
    while (stk.size()) {
        Range range = stk.top();
        stk.pop();
        int level = pow(2, (ll)log2(range.idx));
        int length = powh / level;
        int start = (range.idx % level) * length;
        int mid = start + length / 2;

        if (tree[range.idx].lazy) {
            if (length == 2) {
                tree[2 * range.idx].val += tree[range.idx].lazy;
                tree[2 * range.idx + 1].val += tree[range.idx].lazy;
            } else {
                tree[2 * range.idx].lazy += tree[range.idx].lazy;
                tree[2 * range.idx + 1].lazy += tree[range.idx].lazy;
            }
            tree[range.idx].val += tree[range.idx].lazy * length;
            tree[range.idx].lazy = 0;
        }
        if (range.l == start && range.r - range.l + 1 == length)
            res += tree[range.idx].val;
        else if (range.r < mid)
            stk.push({range.l, range.r, 2 * range.idx});
        else if (mid <= range.l)
            stk.push({range.l, range.r, 2 * range.idx + 1});
        else {
            stk.push({range.l, mid - 1, 2 * range.idx});
            stk.push({mid, range.r, 2 * range.idx + 1});
        }
    }
    return res;
}
void update(int l, int r, ll c) {
    stack<Range> stk;
    stk.push({l, r, 1});
    while (stk.size()) {
        Range range = stk.top();
        stk.pop();
        int level = pow(2, (ll)log2(range.idx));
        int length = powh / level;
        int start = (range.idx % level) * length;
        int mid = start + length / 2;

        if (tree[range.idx].lazy) {
            if (length == 2) {
                tree[2 * range.idx].val += tree[range.idx].lazy;
                tree[2 * range.idx + 1].val += tree[range.idx].lazy;
            } else {
                tree[2 * range.idx].lazy += tree[range.idx].lazy;
                tree[2 * range.idx + 1].lazy += tree[range.idx].lazy;
            }
            tree[range.idx].val += tree[range.idx].lazy * length;
            tree[range.idx].lazy = 0;
        }
        if (range.l == start && range.r - range.l + 1 == length) {
            if (length == 1)
                tree[range.idx].val += c;
            else
                tree[range.idx].lazy = c;
            
            while (range.idx > 1) {
                range.idx >>= 1;
                tree[range.idx].val += length * c;
            }
        } else if (range.r < mid)
            stk.push({range.l, range.r, 2 * range.idx});
        else if (mid <= range.l)
            stk.push({range.l, range.r, 2 * range.idx + 1});
        else {
            stk.push({range.l, mid - 1, 2 * range.idx});
            stk.push({mid, range.r, 2 * range.idx + 1});
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M >> K;
    int height = ceil(log2(N));
    powh = pow(2, height);
    
    for (int i = 0; i < N; i++)
        cin >> tree[powh + i].val;
    
    for (ll h = height - 1; h > -1; h--) {
        for (ll i = pow(2, h); i < pow(2, h + 1); i++)
            tree[i].val = tree[2 * i].val + tree[2 * i + 1].val;
    }
    for (int i = 0; i < M + K; i++) {
        int q, l, r;
        cin >> q >> l >> r;
        if (q == 1) {
            ll v;
            cin >> v;
            update(--l, --r, v);
        } else
            cout << summation(--l, --r) << '\n';
    }
}
