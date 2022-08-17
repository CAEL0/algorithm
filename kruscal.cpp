// BOJ 1197 최소 스패닝 트리

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int V, E, dsu[10005];

struct Edge {
    int x, y, w;
    bool operator<(const Edge &o) const {
        return w < o.w;
    }
} graph[100005];

int find(int z) {
    if (z != dsu[z])
        dsu[z] = find(dsu[z]);
    return dsu[z];
}
void uni(int x, int y) {
    x = find(x);
    y = find(y);
    dsu[x] = y;
}
int kruskal() {
    int ans = 0, cnt = 0;
    for (int i = 0; i < E; i++) {
        if (find(graph[i].x) != find(graph[i].y)) {
            uni(graph[i].x, graph[i].y);
            ans += graph[i].w;
            cnt++;
        }
        if (cnt == V - 1)
            return ans;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> V >> E;
    
    int a, b, c;
    for (int i = 0; i < E; i++) {
        cin >> a >> b >> c;
        graph[i] = Edge{a, b, c};
    }
    sort(graph, graph + E);
    for (int i = 1; i <= V; i++)
        dsu[i] = i;
    
    cout << kruskal();
}
