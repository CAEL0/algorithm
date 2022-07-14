// BOJ 1717 집합의 표현

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int parent[1000000];

int find(int z) {
    if (z != parent[z])
        parent[z] = find(parent[z]);
    return parent[z];
}
void uni(int x, int y) {
    x = find(x);
    y = find(y);
    parent[min(x, y)] = max(x, y);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, q, x, y;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        parent[i] = i;

    while (m--) {
        cin >> q >> x >> y;
        if (q)
            cout << (find(x) == find(y) ? "YES" : "NO") << '\n';
        else
            uni(x, y);
    }
}
