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
int V, E;
vector<pii> G[MAX];
bool vst[MAX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> V >> E;

    while (E--) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back(pii(-w, v));
        G[v].push_back(pii(-w, u));
    }
    int ans = 0;
    int cur = 1;
    priority_queue<pii> pq;
    vst[1] = 1;
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < G[cur].sz; j++)
            if (!vst[G[cur][j].se])
                pq.push(G[cur][j]);
        
        while (1) {
            int w;
            tie(w, cur) = pq.top();
            pq.pop();
            if (!vst[cur]) {
                vst[cur] = 1;
                ans -= w;
                break;
            }
        }
    }
    cout << ans;
}
