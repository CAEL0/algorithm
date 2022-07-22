// BOJ 17469 트리의 색깔과 쿼리

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int N, Q;
int parent[100005], dsu[100005];
set<int> color[100005];

struct Query {
    int x, a, ans;
} query[1100010];

int find(int z) {
    if (z != dsu[z])
        dsu[z] = find(dsu[z]);
    return dsu[z];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> Q;

    for (int i = 2; i <= N; i++)
        cin >> parent[i];
    
    for (int i = 1; i <= N; i++) {
        int tmp;
        cin >> tmp;
        color[i].insert(tmp);
        dsu[i] = i;
    }
    Q += N - 1;
    for (int i = 0; i < Q; i++) {
        int x, a;
        cin >> x >> a;
        query[i] = {x, a};
    }
    for (int i = Q - 1; i >= 0; i--) {
        if (query[i].x == 1) {
            int u = query[i].a;
            int v = parent[u];
            u = find(u);
            v = find(v);
            if (color[u].size() < color[v].size())
                swap(u, v);
            
            dsu[v] = u;
            for (int c: color[v])
                color[u].insert(c);
            color[v].clear();
        } else {
            query[i].ans = color[find(query[i].a)].size();
        }
    }
    for (int i = 0; i < Q; i++)
        if (query[i].x == 2)
            cout << query[i].ans << '\n';
}
