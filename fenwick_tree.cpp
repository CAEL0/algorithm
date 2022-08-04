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
int N;
ll tree[MAX];

struct Fenwick {
    ll summation(int k) {
        ll ret = 0;
        while (k > 0) {
            ret += tree[k];
            k -= (k & -k);
        }
        return ret;
    }
    ll summation(int l, int r) {
        return summation(r) - summation(l - 1);
    }
    ll kth(ll k) {
        ll ret = 0;
        ll idx = 1;
        while (idx <= N)
            idx *= 2;
        
        while (idx) {
            if (ret + idx <= N && tree[ret + idx] < k) {
                k -= tree[ret + idx];
                ret += idx;
            }
            idx /= 2;
        }
        return ret + 1;
    }
    void update(int k, ll v) {
        ll gap = v - summation(k, k);
        while (k <= N) {
            tree[k] += gap;
            k += (k & -k);
        }
    }
    void add(int k, ll v) {
        while (k <= N) {
            tree[k] += v;
            k += (k & -k);
        }
    }
} fw;
