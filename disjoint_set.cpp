// BOJ 1717 집합의 표현

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 1000005;
int N, Q, dsu[MAX], rnk[MAX];

int find(int z) {
    if (z != dsu[z])
        dsu[z] = find(dsu[z]);
    return dsu[z];
}
void uni(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y)
        return;
    
    if (rnk[x] < rnk[y])
        swap(x, y);
    
    rnk[x] += rnk[y];
    dsu[y] = x;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> Q;

    for (int i = 1; i <= N; i++) {
        dsu[i] = i;
        rnk[i] = 1;
    }

    while (Q--) {
        int q, x, y;
        cin >> q >> x >> y;
        if (q == 1)
            cout << (find(x) == find(y) ? "YES" : "NO") << '\n';
        else
            uni(x, y);
    }
}
