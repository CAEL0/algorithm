// BOJ 11438 LCA 2

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 100005;
int N, Q, depth[MAX], sparse[20][MAX];
vector<int> graph[MAX];

void dfs(int cur, int d) {
    depth[cur] = d;
    for (int nxt: graph[cur]) {
        if (!depth[nxt]) {
            sparse[0][nxt] = cur;
            dfs(nxt, d + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    dfs(1, 1);
    for (int i = 0; i < 19; i++)
        for (int j = 1; j <= N; j++)
            sparse[i + 1][j] = sparse[i][sparse[i][j]];
    
    cin >> Q;
    while (Q--) {
        int a, b;
        cin >> a >> b;

        if (depth[a] > depth[b])
            swap(a, b);
        
        int d = depth[b] - depth[a];
        for (int j = 0; j < 20; j++)
            if (d & (1 << j))
                b = sparse[j][b];
        
        if (a == b)
            cout << a << '\n';
        else {
            while (1) {
                for (int j = 19; j >= 0; j--) {
                    if (sparse[j][a] != sparse[j][b]) {
                        a = sparse[j][a];
                        b = sparse[j][b];
                    }
                }
                if (sparse[0][a] == sparse[0][b])
                    cout << sparse[0][a] << '\n';
                    break;
            }
        }
    }
}
