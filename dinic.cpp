// BOJ 13161 분단의 슬픔

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

void add_edge(int from, int to, int capacity, vector<vector<pair<pii, int>>> &graph) {
    int from_idx = graph[from].sz;
    int to_idx = graph[to].sz;

    graph[from].push_back(make_pair(make_pair(to, to_idx), capacity));
    graph[to].push_back(make_pair(make_pair(from, from_idx), 0));
}

int dfs(int cur, int flow, vector<vector<pair<pii, int>>> &graph, vector<int> &level, vector<int> &work, int source) {
    if (cur == source)
        return flow;

    int ret = 0;
    int level_cur = level[cur];
    work[cur]--;
    while (++work[cur] < graph[cur].sz) {
        pair<pii, int> nxt = graph[cur][work[cur]];
        if (level_cur <= level[nxt.fi.fi] || graph[nxt.fi.fi][nxt.fi.se].se == 0)
            continue;

        int k = dfs(nxt.fi.fi, min(flow - ret, graph[nxt.fi.fi][nxt.fi.se].se), graph, level, work, source);
        if (k <= 0)
            continue;

        graph[cur][work[cur]].se += k;
        graph[nxt.fi.fi][nxt.fi.se].se -= k;
        ret += k;

        if (ret == flow)
            return ret;
    }

    level[cur] = graph.sz;
    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    int source = n + 1;
    int sink = n + 2;
    vector<vector<pair<pii, int>>> graph(n + 3);
    for (int i = 1; i <= n; i++) {
        if (v[i] == 1)
            add_edge(source, i, INT_MAX, graph);
        else if (v[i] == 2)
            add_edge(i, sink, INT_MAX, graph);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int k;
            cin >> k;

            if (k > 0)
                add_edge(i, j, k, graph);
        }
    }

    int ans = 0;
    vector<int> level(n + 3);
    vector<int> work(n + 3);
    deque<int> dq;
    while (1) {
        fill(level.begin(), level.end(), -1);
        level[source] = 0;
        dq = {source};
        while (dq.sz) {
            int cur = dq.front();
            dq.pop_front();

            for (auto nxt : graph[cur]) {
                if (nxt.se == 0 || level[nxt.fi.fi] >= 0)
                    continue;

                level[nxt.fi.fi] = level[cur] + 1;
                if (nxt.fi.fi == sink)
                    break;

                dq.push_back(nxt.fi.fi);
            }

            if (level[sink] != -1)
                break;
        }

        if (level[sink] == -1)
            break;

        fill(work.begin(), work.end(), 0);
        while (1) {
            int flow = dfs(sink, INT_MAX, graph, level, work, source);
            ans += flow;
            if (flow == 0)
                break;
        }
    }

    dq = {source};
    vector<bool> vst(n + 3);
    while (dq.sz) {
        int cur = dq.front();
        dq.pop_front();

        for (int i = 0; i < graph[cur].sz; i++) {
            int nxt = graph[cur][i].fi.fi;
            if (graph[cur][i].se && !vst[nxt]) {
                vst[nxt] = true;
                dq.push_back(nxt);
            }
        }
    }

    cout << ans << '\n';

    for (int i = 1; i <= n; i++)
        if (vst[i])
            cout << i << ' ';
    cout << '\n';

    for (int i = 1; i <= n; i++)
        if (!vst[i])
            cout << i << ' ';
    cout << '\n';
}

//--------------------------------------------------------------------------------

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int dfs(int cur, int f, vector<vector<int>> &graph, vector<vector<int>> &capacity, vector<vector<int>> &flow, vector<int> &level, vector<int> &work, int sink) {
    if (cur == sink)
        return f;

    work[cur]--;
    while (++work[cur] < graph[cur].sz) {
        int nxt = graph[cur][work[cur]];
        if (capacity[cur][nxt] <= flow[cur][nxt] || level[nxt] != level[cur] + 1)
            continue;

        int k = dfs(nxt, min(capacity[cur][nxt] - flow[cur][nxt], f), graph, capacity, flow, level, work, sink);
        if (k > 0) {
            flow[cur][nxt] += k;
            flow[nxt][cur] -= k;
            return k;
        }
    }

    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int source = n + 1;
    int sink = n + 2;
    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    vector<vector<int>> graph(n + 3);
    vector<vector<int>> capacity(n + 3, vector<int>(n + 3));
    vector<vector<int>> flow(n + 3, vector<int>(n + 3));
    for (int i = 1; i <= n; i++) {
        if (v[i] == 1) {
            graph[source].push_back(i);
            graph[i].push_back(source);
            capacity[source][i] = INT_MAX;
        } else if (v[i] == 2) {
            graph[i].push_back(sink);
            graph[sink].push_back(i);
            capacity[i][sink] = INT_MAX;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> capacity[i][j];

            if (capacity[i][j])
                graph[i].push_back(j);
        }
    }

    int ans = 0;
    vector<int> level(n + 3);
    vector<int> work(n + 3);
    deque<int> dq;
    while (1) {
        fill(level.begin(), level.end(), -1);
        level[source] = 0;
        dq = {source};
        while (dq.sz) {
            int cur = dq.front();
            dq.pop_front();

            for (int nxt : graph[cur]) {
                if (capacity[cur][nxt] > flow[cur][nxt] && level[nxt] == -1) {
                    level[nxt] = level[cur] + 1;
                    dq.push_back(nxt);
                }
            }
        }

        if (level[sink] == -1)
            break;

        fill(work.begin(), work.end(), 0);
        while (1) {
            int k = dfs(source, INT_MAX, graph, capacity, flow, level, work, sink);
            ans += k;
            if (k == 0)
                break;
        }
    }

    dq = {source};
    vector<bool> vst(n + 3);
    while (dq.sz) {
        int cur = dq.front();
        dq.pop_front();

        for (int nxt : graph[cur]) {
            if (capacity[cur][nxt] > flow[cur][nxt] && !vst[nxt]) {
                vst[nxt] = true;
                dq.push_back(nxt);
            }
        }
    }

    cout << ans << '\n';
    
    for (int i = 1; i <= n; i++)
        if (vst[i])
            cout << i << ' ';
    cout << '\n';

    for (int i = 1; i <= n; i++)
        if (!vst[i])
            cout << i << ' ';
    cout << '\n';
}
