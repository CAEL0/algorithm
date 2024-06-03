// BOJ 2188 축사 배정

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

bool dfs(int cur, vector<int> &a, vector<int> &b, vector<int> &lvl, vector<vector<int>> &graph) {
    for (int nxt : graph[cur]) {
        if (lvl[b[nxt]] == lvl[cur] + 1 && (b[nxt] == 0 || dfs(b[nxt], a, b, lvl, graph))) {
            a[cur] = nxt;
            b[nxt] = cur;
            return true;
        }
    }

    lvl[cur] = INT_MAX;
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);

    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;

        while (k--) {
            int x;
            cin >> x;

            graph[i].push_back(x);
        }
    }

    vector<int> a(n + 1);
    vector<int> b(m + 1);
    vector<int> lvl(n + 1);
    int ans = 0;

    while (1) {
        lvl[0] = INT_MAX;
        deque<int> dq;

        for (int i = 1; i <= n; i++) {
            if (a[i] == 0) {
                lvl[i] = 0;
                dq.push_back(i);
            } else
                lvl[i] = INT_MAX;
        }

        while (dq.sz) {
            int cur = dq.front();
            dq.pop_front();

            for (int nxt : graph[cur]) {
                if (lvl[b[nxt]] == INT_MAX) {
                    lvl[b[nxt]] = lvl[cur] + 1;
                    dq.push_back(b[nxt]);
                }
            }
        }

        int flow = 0;
        for (int i = 1; i <= n; i++)
            if (!a[i] && dfs(i, a, b, lvl, graph))
                flow++;

        if (flow == 0)
            break;

        ans += flow;
    }

    cout << ans;
}
