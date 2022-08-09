// BOJ 2188 축사 배정

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int N, M;
vector<int> graph[205];
int b[205];
bool vst[205];

bool dfs(int cur) {
    vst[cur] = true;
    for (int nxt: graph[cur]) {
        if (!b[nxt] || (!vst[b[nxt]] && dfs(b[nxt]))) {
            b[nxt] = cur;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        int s;
        cin >> s;
        while (s--) {
            int tmp;
            cin >> tmp;
            graph[i].push_back(tmp);
        }
    }
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        fill_n(vst, N + 1, false);
        ans += dfs(i);
    }
    cout << ans;
}
