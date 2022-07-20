// BOJ 10999 구간 합 구하기 2

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll powh, tree[4000010], lazy[4000010];

struct Node {
    ll l, r, idx;
};

ll summation(ll a, ll b) {
    ll res = 0;
    stack<Node> stk;
    stk.push({a, b, 1});
    while (stk.size()) {
        Node node = stk.top();
        stk.pop();
        ll level = pow(2, (ll)log2(node.idx));
        ll length = powh / level;
        ll start = (node.idx % level) * length;
        ll mid = start + length / 2;

        if (lazy[node.idx]) {
            if (length == 2) {
                tree[2 * node.idx] += lazy[node.idx];
                tree[2 * node.idx + 1] += lazy[node.idx];
            }
            else {
                lazy[2 * node.idx] += lazy[node.idx];
                lazy[2 * node.idx + 1] += lazy[node.idx];
            }
            tree[node.idx] += lazy[node.idx] * length;
            lazy[node.idx] = 0;
        }
        if (node.l == start && node.r - node.l + 1 == length)
            res += tree[node.idx];
        else if (node.r < mid)
            stk.push({node.l, node.r, 2 * node.idx});
        else if (mid <= node.l)
            stk.push({node.l, node.r, 2 * node.idx + 1});
        else {
            stk.push({node.l, mid - 1, 2 * node.idx});
            stk.push({mid, node.r, 2 * node.idx + 1});
        }
    }
    return res;
}
void update(ll a, ll b, ll c) {
    stack<Node> stk;
    stk.push({a, b, 1});
    while (stk.size()) {
        Node node = stk.top();
        stk.pop();
        ll level = pow(2, (ll)log2(node.idx));
        ll length = powh / level;
        ll start = (node.idx % level) * length;
        ll mid = start + length / 2;

        if (lazy[node.idx]) {
            if (length == 2) {
                tree[2 * node.idx] += lazy[node.idx];
                tree[2 * node.idx + 1] += lazy[node.idx];
            }
            else {
                lazy[2 * node.idx] += lazy[node.idx];
                lazy[2 * node.idx + 1] += lazy[node.idx];
            }
            tree[node.idx] += lazy[node.idx] * length;
            lazy[node.idx] = 0;
        }
        if (node.l == start && node.r - node.l + 1 == length) {
            if (length == 1)
                tree[node.idx] += c;
            else
                lazy[node.idx] = c;
            
            while (node.idx > 1) {
                node.idx >>= 1;
                tree[node.idx] += length * c;
            }
        }
        else if (node.r < mid)
            stk.push({node.l, node.r, 2 * node.idx});
        else if (mid <= node.l)
            stk.push({node.l, node.r, 2 * node.idx + 1});
        else {
            stk.push({node.l, mid - 1, 2 * node.idx});
            stk.push({mid, node.r, 2 * node.idx + 1});
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll n, m, k, height;
    cin >> n >> m >> k;
    height = (ll)ceil(log2(n));
    powh = pow(2, height);
    
    for (int i = 0; i < n; i++)
        cin >> tree[powh + i];
    
    for (ll h = height - 1; h > -1; h--) {
        for (ll i = pow(2, h); i < pow(2, h + 1); i++)
            tree[i] = tree[2 * i] + tree[2 * i + 1];
    }
    for (ll a, b, c, q, i = 0; i < m + k; i++) {
        cin >> q >> a >> b;
        if (q == 1) {
            cin >> c;
            update(a - 1, b - 1, c);
        } else
            cout << summation(a - 1, b - 1) << '\n';
    }
}
