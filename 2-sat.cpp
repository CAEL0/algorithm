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
int idx, scc_num;
vector<int> stk, vst(MAX), scc_idx(MAX), finish(MAX);
vector<vector<int>> grp(MAX);

int dfs(int cur) {
    stk.push_back(cur);
    vst[cur] = idx;
    int low = idx++;
    for (int nxt : grp[cur]) {
        if (not vst[nxt])
            low = min(low, dfs(nxt));
        else if (not finish[nxt])
            low = min(low, vst[nxt]);
    }
    if (low == vst[cur]) {
        while (1) {
            int top = stk.bk;
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
                grp[(-2) * x - 1].push_back((-2) * y);
                grp[(-2) * y - 1].push_back((-2) * x);
            } else {
                grp[(-2) * x - 1].push_back(2 * y - 1);
                grp[2 * y].push_back((-2) * x);
            }
        } else if (y < 0) {
            grp[2 * x].push_back((-2) * y);
            grp[(-2) * y - 1].push_back(2 * x - 1);
        } else {
            grp[2 * x].push_back(2 * y - 1);
            grp[2 * y].push_back(2 * x - 1);
        }
    }
    idx = 1;
    scc_num = 1;
    for (int i = 1; i <= 2 * n; i++)
        if (not vst[i])
            dfs(i);
    
    for (int i = 1; i <= n; i++) {
        if (scc_idx[2 * i - 1] == scc_idx[2 * i]) {
            cout << 0;
            return 0;
        }
    }
    cout << "1\n";
    for (int i = 1; i <= n; i++)
        cout << (scc_idx[2 * i - 1] < scc_idx[2 * i]) << ' ';
}
