// BOJ 1199 오일러 회로

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int N;
int graph[1005][1005];

void dfs(int i) {
    for (int j = 1; j <= N; j++) {
        int tmp = 0;
        while (graph[i][j] > 2) {
            graph[i][j] -= 2;
            graph[j][i] -= 2;
            tmp++;
        }
        if (graph[i][j]) {
            graph[i][j]--;
            graph[j][i]--;
            dfs(j);
            cout << j << ' ';
            while (tmp--) {
                cout << i << ' ' << j << ' ';
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;

    for (int i = 1; i <= N; i++) {
        int deg = 0;
        for (int j = 1; j <= N; j++) {
            cin >> graph[i][j];
            deg += graph[i][j];
        }
        if (deg & 1) {
            cout << -1;
            return 0;
        }
    }
    dfs(1);
    cout << 1;
}
