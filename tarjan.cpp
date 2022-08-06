// BOJ 2150 Strongly Connected Component

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 10005;
int V, E, idx = 1, vst[MAX];
bool fin[MAX];
vector<int> graph[MAX], stk;
vector<vector<int>> scc;

int dfs(int cur) {
    vst[cur] = idx;
    int low = idx++;
    stk.push_back(cur);

    for (int nxt: graph[cur]) {
        if (!vst[nxt])
            low = min(low, dfs(nxt));
        else if (!fin[nxt])
            low = min(low, vst[nxt]);
    }
    if (low == vst[cur]) {
        vector<int> res;
        while (stk.sz) {
            int top = stk.bk;
            stk.pop_back();
            fin[top] = true;
            res.push_back(top);
            if (cur == top)
                break;
        }
        scc.push_back(res);
    }
    return low;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> V >> E;
    while (E--) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
    }
    for (int i = 1; i <= V; i++)
        if (!vst[i])
            dfs(i);

    for (auto &res: scc)
        sort(res.begin(), res.end());
    sort(scc.begin(), scc.end());

    cout << scc.sz << '\n';
    for (vector<int> res: scc) {
        for (int i: res)
            cout << i << ' ';
        cout << -1 << '\n';
    }
}
