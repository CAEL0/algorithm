// BOJ 1717 집합의 표현

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 1000005;
int n, q, dsu[MAX], rnk[MAX];

void init() {
    for (int i = 1; i <= n; i++) {
        dsu[i] = i;
        rnk[i] = 1;
    }
}

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
    cin.tie(0);
    cout.tie(0);

    cin >> n >> q;
    init();
    while (q--) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1)
            cout << (find(x) == find(y) ? "YES" : "NO") << '\n';
        else
            uni(x, y);
    }
}
