// BOJ 2820 자동차 공장

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 500005;
int N, Q, idx, A[MAX], in[MAX], out[MAX];
ll tree[4 * MAX];
vector<int> graph[MAX];

void dfs(int cur) {
    in[cur] = ++idx;
    for (int nxt: graph[cur])
        dfs(nxt);

    out[cur] = idx;
}
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

    cin >> N >> Q >> A[1];
    for (int i = 2; i <= N; i++) {
        int p;
        cin >> A[i] >> p;
        graph[p].push_back(i);
    }
    dfs(1);
    while (Q--) {
        char q;
        cin >> q;
        if (q == 'p') {
            int a, x;
            cin >> a >> x;
            range(1, 1, N, in[a] + 1, out[a], x);
        } else {
            int a;
            cin >> a;
            cout << point(1, 1, N, in[a]) + A[a] << '\n';
        }
    }
}
