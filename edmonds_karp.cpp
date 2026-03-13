// BOJ 17412 도시 왕복하기 1

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct EdmondsKarp {
    int n, source, sink;
    vector<vector<int>> graph, capacity, flow;

    EdmondsKarp(int n) : n(n) {
        source = n + 1;
        sink = n + 2;
        graph.resize(n + 3);
        capacity.resize(n + 3, vector<int>(n + 3));
        flow.resize(n + 3, vector<int>(n + 3));
    }

    EdmondsKarp(int n, int source, int sink) : n(n), source(source), sink(sink) {
        graph.resize(n + 1);
        capacity.resize(n + 1, vector<int>(n + 1));
        flow.resize(n + 1, vector<int>(n + 1));
    }

    void add_from_source(int to, int cap) { add_edge(source, to, cap); }

    void add_to_sink(int from, int cap) { add_edge(from, sink, cap); }

    void add_edge(int from, int to, int cap) {
        graph[from].push_back(to);
        graph[to].push_back(from);
        capacity[from][to] = cap;
    }

    int maximum_flow() {
        int ret = 0;
        while (1) {
            vector<int> prv(graph.sz, -1);
            deque<int> dq = {source};
            while (dq.sz && prv[sink] == -1) {
                int cur = dq.front();
                dq.pop_front();

                for (int nxt : graph[cur]) {
                    if (flow[cur][nxt] < capacity[cur][nxt] && prv[nxt] == -1) {
                        prv[nxt] = cur;
                        dq.push_back(nxt);

                        if (nxt == sink)
                            break;
                    }
                }
            }

            if (prv[sink] == -1)
                break;

            int f = INT_MAX;
            int nxt = sink;
            while (nxt != source) {
                int cur = prv[nxt];
                f = min(f, capacity[cur][nxt] - flow[cur][nxt]);
                nxt = cur;
            }

            ret += f;
            nxt = sink;
            while (nxt != source) {
                int cur = prv[nxt];
                flow[cur][nxt] += f;
                flow[nxt][cur] -= f;
                nxt = cur;
            }
        }

        return ret;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    EdmondsKarp ek(n, 1, 2);
    while (m--) {
        int x, y;
        cin >> x >> y;

        ek.add_edge(x, y, 1);
    }

    cout << ek.maximum_flow();
}
