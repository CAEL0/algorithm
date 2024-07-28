// BOJ 2252 줄 세우기

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1);

    while (m--) {
        int x, y;
        cin >> x >> y;

        graph[x].push_back(y);
        indegree[y]++;
    }

    deque<int> dq;
    for (int i = 1; i <= n; i++)
        if (indegree[i] == 0)
            dq.push_back(i);

    while (dq.sz) {
        int cur = dq.front();
        dq.pop_front();

        cout << cur << ' ';

        for (int nxt : graph[cur])
            if (--indegree[nxt] == 0)
                dq.push_back(nxt);
    }
}
