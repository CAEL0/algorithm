// BOJ 2252 줄 세우기

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 32005;
int N, M, ind[MAX];
vector<int> G[MAX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;
    while (M--) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        ind[b]++;
    }
    queue<int> qu;
    for (int i = 1; i <= N; i++) {
        if (ind[i] == 0) {
            qu.push(i);
            cout << i << ' ';
        }
    }
    while (qu.sz) {
        int x = qu.front();
        qu.pop();

        for (int y: G[x]) {
            if (--ind[y] == 0) {
                qu.push(y);
                cout << y << ' ';
            }
        }
    }
}
