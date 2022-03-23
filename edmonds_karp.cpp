// BOJ 2188 축사 배정

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, k;
    cin >> n >> m;
    k = n + m + 2;
    vector<int> graph[k];
    
    for (int j, tmp, i = 1; i < n + 1; i++) {
        graph[0].push_back(i);
        cin >> j;
        while (j--) {
            cin >> tmp;
            graph[i].push_back(n + tmp);
        }
    }
    for (int i = n + 1; i < k - 1; i++)
        graph[i].push_back(k - 1);

    int ans = 0;
    while (true) {
        int prev[k];
        fill_n(prev, k, -1);
        deque<int> dq;
        dq.push_back(0);
        while (!dq.empty()) {
            int cur = dq.front();
            dq.pop_front();
            for (int nxt : graph[cur]) {
                if (nxt == k - 1) {
                    prev[k - 1] = cur;
                    break;
                }
                if (prev[nxt] == -1) {
                    prev[nxt] = cur;
                    dq.push_back(nxt);
                }
            }
            if (prev[k - 1] != -1) break;
        }
        if (prev[k - 1] == -1) break;
        ans++;
        int nxt = k - 1;
        while (nxt) {
            int cur = prev[nxt];
            for (int i = 0; i < graph[cur].size(); i++) {
                if (graph[cur][i] == nxt) {
                    graph[cur].erase(graph[cur].begin() + i);
                    break;
                }
            }
            graph[nxt].push_back(cur);
            nxt = cur;
        }
    }
    cout << ans;
}
