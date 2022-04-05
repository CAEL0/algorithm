// BOJ 10999 구간 합 구하기 2

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef tuple<ll, ll, ll> tll;

ll z, tree[4000010], lazy[4000010];

ll summation(ll a, ll b) {
    ll res = 0;
    vector<tll> queue;
    queue.push_back(tll(a, b, 1));
    while (queue.size()) {
        ll l, r, idx;
        tie(l, r, idx) = queue.back();
        queue.pop_back();
        ll level = pow(2, (ll)log2(idx));
        ll length = z / level;
        ll start = (idx % level) * length;
        ll mid = start + length / 2;

        if (lazy[idx]) {
            if (length == 2) {
                tree[2 * idx] += lazy[idx];
                tree[2 * idx + 1] += lazy[idx];
            }
            else {
                lazy[2 * idx] += lazy[idx];
                lazy[2 * idx + 1] += lazy[idx];
            }
            tree[idx] += lazy[idx] * length;
            lazy[idx] = 0;
        }
        if (l == start && r - l + 1 == length)
            res += tree[idx];
        else if (r < mid)
            queue.push_back(tll(l, r, 2 * idx));
        else if (mid <= l)
            queue.push_back(tll(l, r, 2 * idx + 1));
        else {
            queue.push_back(tll(l, mid - 1, 2 * idx));
            queue.push_back(tll(mid, r, 2 * idx + 1));
        }
    }
    return res;
}
void update(ll a, ll b, ll c) {
    vector<tll> queue;
    queue.push_back(tll(a, b, 1));
    while (queue.size()) {
        ll l, r, idx;
        tie(l, r, idx) = queue.back();
        queue.pop_back();
        ll level = pow(2, (ll)log2(idx));
        ll length = z / level;
        ll start = (idx % level) * length;
        ll mid = start + length / 2;

        if (lazy[idx]) {
            if (length == 2) {
                tree[2 * idx] += lazy[idx];
                tree[2 * idx + 1] += lazy[idx];
            }
            else {
                lazy[2 * idx] += lazy[idx];
                lazy[2 * idx + 1] += lazy[idx];
            }
            tree[idx] += lazy[idx] * length;
            lazy[idx] = 0;
        }
        if (l == start && r - l + 1 == length) {
            if (length == 1)
                tree[idx] += c;
            else
                lazy[idx] = c;
            
            while (idx > 1) {
                idx /= 2;
                tree[idx] += length * c;
            }
        }
        else if (r < mid)
            queue.push_back(tll(l, r, 2 * idx));
        else if (mid <= l)
            queue.push_back(tll(l, r, 2 * idx + 1));
        else {
            queue.push_back(tll(l, mid - 1, 2 * idx));
            queue.push_back(tll(mid, r, 2 * idx + 1));
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    ll n, m, k, height;
    cin >> n >> m >> k;
    height = (ll)ceil(log2(n));
    z = pow(2, height);
    
    for (int i = 0; i < n; i++)
        cin >> tree[z + i];
    
    for (ll h = height - 1; h > -1; h--) {
        for (ll i = pow(2, h); i < pow(2, h + 1); i++)
            tree[i] = tree[2 * i] + tree[2 * i + 1];
    }
    for (ll a, b, c, q, i = 0; i < m + k; i++) {
        cin >> q >> a >> b;
        if (q == 1) {
            cin >> c;
            update(a - 1, b - 1, c);
        }
        else
            cout << summation(a - 1, b - 1) << '\n';
    }
}
