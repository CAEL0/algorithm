// BOJ 11281 2-SAT - 4

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int idx, scc_num;
vector<int> stk, vst(1000000), scc_idx(1000000), finish(1000000);
vector<vector<int>> graph(1000000);

int dfs(int cur) {
    stk.push_back(cur);
    vst[cur] = idx;
    int low = idx++;
    for (int nxt : graph[cur]) {
        if (not vst[nxt])
            low = min(low, dfs(nxt));
        else if (not finish[nxt])
            low = min(low, vst[nxt]);
    }
    if (low == vst[cur]) {
        while (true) {
            int top = stk.back();
            stk.pop_back();
            finish[top] = 1;
            scc_idx[top] = scc_num;
            if (cur == top)
                break;
        }
        scc_num++;
    }
    return low;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;

    while (m--) {
        int x, y;
        cin >> x >> y;
        if (x < 0) {
            if (y < 0) {
                graph[(-2) * x - 1].push_back((-2) * y);
                graph[(-2) * y - 1].push_back((-2) * x);
            } else {
                graph[(-2) * x - 1].push_back(2 * y - 1);
                graph[2 * y].push_back((-2) * x);
            }
        } else if (y < 0) {
            graph[2 * x].push_back((-2) * y);
            graph[(-2) * y - 1].push_back(2 * x - 1);
        } else {
            graph[2 * x].push_back(2 * y - 1);
            graph[2 * y].push_back(2 * x - 1);
        }
    }
    idx = 1;
    scc_num = 1;
    
    for (int i = 1; i < 2 * n + 1; i++)
        if (not vst[i])
            dfs(i);
    
    bool flag = true;
    for (int i = 0; i < n; i++) {
        if (scc_idx[2 * i + 1] == scc_idx[2 * i + 2]) {
            cout << 0;
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << "1\n";
        for (int i = 0; i < n; i++)
            cout << (scc_idx[2 * i + 1] < scc_idx[2 * i + 2]) << ' ';
    }
}
