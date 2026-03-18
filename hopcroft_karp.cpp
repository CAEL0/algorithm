// BOJ 2051 최소 버텍스 커버

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct HopcroftKarp {
    int n, m;
    vector<int> a, b, lvl;
    vector<vector<int>> graph;

    HopcroftKarp(int n, int m) : n(n), m(m) {
        a.resize(n + 1);
        b.resize(m + 1);
        lvl.resize(n + 1);
        graph.resize(n + 1);
    }

    void add_edge(int x, int y) { graph[x].push_back(y); }

    int maximum_matching() {
        int ret = 0;
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
                if (!a[i] && dfs(i))
                    flow++;

            if (flow == 0)
                break;

            ret += flow;
        }

        return ret;
    }

    bool dfs(int cur) {
        for (int nxt : graph[cur]) {
            if (lvl[b[nxt]] == lvl[cur] + 1 && (b[nxt] == 0 || dfs(b[nxt]))) {
                a[cur] = nxt;
                b[nxt] = cur;
                return true;
            }
        }

        lvl[cur] = INT_MAX;
        return false;
    }

    void minimum_vertex_cover(int cur, vector<bool> &left, vector<bool> &right) {
        for (int nxt : graph[cur]) {
            if (a[cur] == nxt || right[nxt])
                continue;

            right[nxt] = true;
            if (!left[b[nxt]]) {
                left[b[nxt]] = true;
                minimum_vertex_cover(b[nxt], left, right);
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    HopcroftKarp hk(n, m);
    for (int i = 1; i <= n; i++) {
        int k;
        cin >> k;

        while (k--) {
            int j;
            cin >> j;

            hk.add_edge(i, j);
        }
    }

    cout << hk.maximum_matching() << '\n';

    vector<bool> left(n + 1);
    vector<bool> right(m + 1);
    for (int i = 1; i <= n; i++) {
        if (hk.a[i] == 0 && !left[i]) {
            left[i] = true;
            hk.minimum_vertex_cover(i, left, right);
        }
    }

    vector<int> left_ans;
    for (int i = 1; i <= n; i++)
        if (!left[i])
            left_ans.push_back(i);

    vector<int> right_ans;
    for (int j = 1; j <= m; j++)
        if (right[j])
            right_ans.push_back(j);

    cout << left_ans.sz << ' ';
    for (int x : left_ans)
        cout << x << ' ';
    cout << '\n';

    cout << right_ans.sz << ' ';
    for (int x : right_ans)
        cout << x << ' ';
    cout << '\n';
}
