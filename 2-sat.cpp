// BOJ 11281 2-SAT - 4

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int dfs(int cur, int &idx, int &scc_num, vector<int> &v, vector<int> &vst, vector<int> &scc_idx, vector<int> &finish, vector<vector<int>> &graph) {
    v.push_back(cur);
    vst[cur] = idx;
    int low = idx++;

    for (int nxt : graph[cur]) {
        if (!vst[nxt])
            low = min(low, dfs(nxt, idx, scc_num, v, vst, scc_idx, finish, graph));
        else if (!finish[nxt])
            low = min(low, vst[nxt]);
    }

    if (low != vst[cur])
        return low;

    while (1) {
        int top = v.bk;
        v.pop_back();

        finish[top] = 1;
        scc_idx[top] = scc_num;

        if (cur == top)
            break;
    }

    scc_num++;
    return low;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(2 * n + 1);

    while (m--) {
        int x, y;
        cin >> x >> y;

        if (x > 0 && y > 0) {
            graph[2 * x].push_back(2 * y - 1);
            graph[2 * y].push_back(2 * x - 1);
        } else if (x > 0 && y < 0) {
            graph[2 * x].push_back(-2 * y);
            graph[-2 * y - 1].push_back(2 * x - 1);
        } else if (x < 0 && y > 0) {
            graph[-2 * x - 1].push_back(2 * y - 1);
            graph[2 * y].push_back(-2 * x);
        } else if (x < 0 && y < 0) {
            graph[-2 * x - 1].push_back(-2 * y);
            graph[-2 * y - 1].push_back(-2 * x);
        }
    }

    int idx = 1;
    int scc_num = 1;
    vector<int> v, vst(2 * n + 1), scc_idx(2 * n + 1), finish(2 * n + 1);

    for (int i = 1; i <= 2 * n; i++)
        if (!vst[i])
            dfs(i, idx, scc_num, v, vst, scc_idx, finish, graph);

    for (int i = 1; i <= n; i++) {
        if (scc_idx[2 * i - 1] == scc_idx[2 * i]) {
            cout << 0;
            return 0;
        }
    }

    cout << 1 << '\n';
    for (int i = 1; i <= n; i++)
        cout << (scc_idx[2 * i - 1] < scc_idx[2 * i]) << ' ';
}
