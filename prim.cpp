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

const int MAX = 10010;
vector<pii> graph[MAX];
bool vst[MAX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int v, e, a, b, c, w;
    cin >> v >> e;

    while (e--) {
        cin >> a >> b >> c;
        graph[a].push_back(pii(-c, b));
        graph[b].push_back(pii(-c, a));
    }
    int ans = 0;
    int cur = 1;
    priority_queue<pii> adj;
    vst[1] = 1;
    for (int i = 0; i < v - 1; i++) {
        for (int j = 0; j < graph[cur].size(); j++)
            if (!vst[graph[cur][j].second])
                adj.push(graph[cur][j]);
        
        while (true) {
            tie(w, cur) = adj.top();
            adj.pop();
            if (!vst[cur]) {
                vst[cur] = 1;
                ans -= w;
                break;
            }
        }
    }
    cout << ans;
}
