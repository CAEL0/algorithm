// BOJ 11404 플로이드

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 105;
int V, E, G[MAX][MAX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> V >> E;
    for (int i = 1; i <= V; i++)
        for (int j = 1; j <= V; j++)
            if (i != j)
                G[i][j] = 1e9;
    
    while (E--) {
        int i, j, w;
        cin >> i >> j >> w;
        G[i][j] = min(G[i][j], w);
    }
    for (int k = 1; k <= V; k++)
        for (int i = 1; i <= V; i++)
            for (int j = 1; j <= V; j++)
                G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
    
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++)
            cout << (G[i][j] == 1e9 ? 0 : G[i][j]) << ' ';
        cout << '\n';
    }
}
