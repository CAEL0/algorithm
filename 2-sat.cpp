#include <iostream>
#include <bits/stdc++.h>

using namespace std;
int MAX = 987654;
int idx, scc_num;
stack<int> S;
vector<int> visit[MAX], scc_idx[MAX], finish[MAX];
vector<vector<int>> graph[MAX];

int dfs(int cur) {
    S.push(cur);
    visit[cur] = idx;
    int low = idx;
    idx++;
    
    for (int nxt : graph[cur]) {
        if (not visit[nxt]) {
            low = min(low, dfs(nxt));
        }
        else if (not finish[nxt]) {
            low = min(low, visit[nxt]);
        }
    }
    
    if (low == visit[cur]) {
        while (true) {
            int top = S.top();
            S.pop();
            finish[top] = 1;
            scc_idx[top] = scc_num;
            if (cur == top) {
                break;
            }
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
            }
            else {
                graph[(-2) * x - 1].push_back(2 * y - 1);
                graph[2 * y].push_back((-2) * x);
            }
        }
        else if (y < 0) {
            graph[2 * x].push_back((-2) * y);
            graph[(-2) * y - 1].push_back(2 * x - 1);
        }
        else {
            graph[2 * x].push_back(2 * y - 1);
            graph[2 * y].push_back(2 * x - 1);
        }
    }

    idx = 1;
    scc_num = 1;
    
    for (int i = 1; i < 2 * n + 1; i++) {
        if (not visit[i]) {
            dfs(i);
        }
    }
    
    bool flag = true;
    for (int i = 0; i < n; i++) {
        if (scc_idx[2 * i + 1] == scc_idx[2 * i + 2]) {
            cout << '0';
            flag = false;
            break;
        }
    }
    if (flag) {
        cout << '1' << '\n';
        for (int i = 0; i < n; i++) cout << (scc_idx[2 * i + 1] < scc_idx[2 * i + 2]) << ' ';
    }
}
