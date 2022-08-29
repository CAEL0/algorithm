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

const int MAX = 205;
int N, M, B[MAX];
vector<int> G[MAX];
bool vst[MAX];

bool dfs(int cur) {
    vst[cur] = true;
    for (int nxt: G[cur]) {
        if (!B[nxt] || (!vst[B[nxt]] && dfs(B[nxt]))) {
            B[nxt] = cur;
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
            G[i].push_back(tmp);
        }
    }
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        fill_n(vst, N + 1, false);
        ans += dfs(i);
    }
    cout << ans;
}
