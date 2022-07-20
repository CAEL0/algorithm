// BOJ 10999 구간 합 구하기 2

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
