// BOJ 1197 최소 스패닝 트리

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int V, E;
int parent[10005];

struct Edge {
    int x, y, w;
    bool operator < (const Edge &e) const {
        return w < e.w;
    }
} graph[100005];

int find(int z) {
    if (z != parent[z])
        parent[z] = find(parent[z]);
    return parent[z];
}
void uni(int x, int y) {
    x = find(x);
    y = find(y);
    parent[min(x, y)] = max(x, y);
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
        parent[i] = i;
    
    cout << kruskal();
}
