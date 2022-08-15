// BOJ 1396 크루스칼의 공

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
int N, M, Q, dsu[MAX], lef[MAX], rig[MAX], sub[MAX], ans[MAX];
struct Edge {
    int u, v, w;
    bool operator<(const Edge &o) const {
        return w < o.w;
    }
} edges[MAX];

struct Query {
    int x, y;
} qry[MAX];

int find(int z) {
    if (z != dsu[z])
        dsu[z] = find(dsu[z]);
    return dsu[z];
}
void uni(int x, int y) {    
    x = find(x);
    y = find(y);
    if (x != y) {
        dsu[x] = y;
        sub[y] += sub[x];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }
    sort(edges + 1, edges + M + 1);
    cin >> Q;
    for (int i = 1; i <= Q; i++)
        cin >> qry[i].x >> qry[i].y;
    
    fill_n(lef, Q + 1, 1);
    fill_n(rig, Q + 1, M);
    while (1) {
        bool flag = true;
        vector<int> G[M + 1];
        for (int q = 1; q <= Q; q++) {
            if (lef[q] <= min(M, rig[q])) {
                flag = false;
                G[(lef[q] + rig[q]) >> 1].push_back(q);
            }
        }
        if (flag)
            break;
        
        fill_n(sub, N + 1, 1);
        for (int i = 1; i <= N; i++)
            dsu[i] = i;
        
        for (int j = 1; j <= M; j++) {
            uni(edges[j].u, edges[j].v);
            for (int q: G[j]) {
                int a = find(qry[q].x);
                int b = find(qry[q].y);
                if (a == b) {
                    rig[q] = j - 1;
                    ans[q] = sub[find(a)];
                } else
                    lef[q] = j + 1;
            }
        }
    }
    for (int q = 1; q <= Q; q++) {
        if (lef[q] > M)
            cout << -1 << '\n';
        else
            cout << edges[lef[q]].w << ' ' << ans[q] << '\n';
    }
}
