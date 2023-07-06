// BOJ 11001 김치

#include <bits/stdc++.h>
#define fi first
#define se second
#define sz size()
#define bk back()

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 100005;
int n, d, t[MAX], v[MAX];
ll ans;

ll f(int i, int j) { return (ll)t[j] * (j - i) + v[i]; }

void g(int s, int e, int l, int r) {
    if (s > e)
        return;

    int i = (s + e) >> 1;
    int k = i;
    for (int j = max(i + 1, l); j <= min(i + d, r); j++)
        if (f(i, k) < f(i, j))
            k = j;

    ans = max(ans, f(i, k));
    g(s, i - 1, l, k);
    g(i + 1, e, k, r);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> d;
    for (int i = 1; i <= n; i++)
        cin >> t[i];

    for (int i = 1; i <= n; i++)
        cin >> v[i];

    g(1, n, 1, n);
    cout << ans;
}
