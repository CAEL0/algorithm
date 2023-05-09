// BOJ 11281 2-SAT - 4

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 1000005;
int N, M, idx, scc_num;
vector<int> S, vst(MAX), scc_idx(MAX), finish(MAX);
vector<vector<int>> G(MAX);

int dfs(int cur) {
    S.push_back(cur);
    vst[cur] = idx;
    int low = idx++;
    for (int nxt : G[cur]) {
        if (not vst[nxt])
            low = min(low, dfs(nxt));
        else if (not finish[nxt])
            low = min(low, vst[nxt]);
    }
    if (low == vst[cur]) {
        while (true) {
            int top = S.bk;
            S.pop_back();
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

    cin >> N >> M;
    while (M--) {
        int x, y;
        cin >> x >> y;
        if (x < 0) {
            if (y < 0) {
                G[(-2) * x - 1].push_back((-2) * y);
                G[(-2) * y - 1].push_back((-2) * x);
            } else {
                G[(-2) * x - 1].push_back(2 * y - 1);
                G[2 * y].push_back((-2) * x);
            }
        } else if (y < 0) {
            G[2 * x].push_back((-2) * y);
            G[(-2) * y - 1].push_back(2 * x - 1);
        } else {
            G[2 * x].push_back(2 * y - 1);
            G[2 * y].push_back(2 * x - 1);
        }
    }
    idx = 1;
    scc_num = 1;
    
    for (int i = 1; i < 2 * N + 1; i++)
        if (not vst[i])
            dfs(i);
    
    for (int i = 0; i < N; i++) {
        if (scc_idx[2 * i + 1] == scc_idx[2 * i + 2]) {
            cout << 0;
            return 0;
        }
    }
    cout << "1\n";
    for (int i = 0; i < N; i++)
        cout << (scc_idx[2 * i + 1] < scc_idx[2 * i + 2]) << ' ';
}
