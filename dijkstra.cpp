// BOJ 1753 최단경로

#include <iostream>
#include <bits/stdc++.h>
#define fi first
#define se second

using namespace std;
typedef pair<int, int> pii;

vector<pii> graph[20001];
int res[20001];

void dijkstra(int start) {
    priority_queue<pii> pq;
    pq.push(pii(0, start));

    while (!pq.empty()) {
        int old_weight, old_node;
        tie(old_weight, old_node) = pq.top();
        pq.pop();

        if (res[old_node] >= -old_weight) {
            for (auto new_item : graph[old_node]) {
                int new_node, new_weight, total_weight;
                tie(new_node, new_weight) = new_item;
                total_weight = -old_weight + new_weight;

                if (total_weight < res[new_node]) {
                    res[new_node] = total_weight;
                    pq.push(pii(-total_weight, new_node));
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int v, e, start;
    cin >> v >> e >> start;

    for (int a, b, c, i = 0; i < e; i++) {
        cin >> a >> b >> c;
        graph[a].push_back(pii(b, c));
    }
    fill_n(res, v + 1, 3000001);
    res[start] = 0;

    dijkstra(start);
    
    for (int i = 1; i < v + 1; i++) {
        if (res[i] == 3000001)
            cout << "INF\n";
        else
            cout << res[i] << '\n';
    }
}
