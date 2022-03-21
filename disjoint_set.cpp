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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, o, x, y;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        parent[i] = i;

    while (m--) {
        cin >> o >> x >> y;
        if (o) {
            if (find(x) == find(y))
                cout << "YES\n";
            else
                cout << "NO\n";
        }
        else
            parent[find(x)] = find(y);
    }
}
