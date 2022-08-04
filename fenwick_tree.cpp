// BOJ 2042 구간 합 구하기

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int N;
ll tree[1000005];

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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int M, K;
    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++) {
        ll v;
        cin >> v;
        fw.add(i, v);
    }
    int Q = M + K;
    while (Q--) {
        ll a, b, c;
        cin >> a >> b >> c;
        if (a == 1)
            fw.update(b, c);
        else
            cout << fw.summation(b, c) << '\n';
    }
}
