// BOJ 11659 구간 합 구하기 4

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    vector<ll> v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    vector<ll> prefix_sum(n + 1);
    for (int i = 1; i <= n; i++)
        prefix_sum[i] = prefix_sum[i - 1] + v[i];

    while (q--) {
        int x, y;
        cin >> x >> y;

        cout << prefix_sum[y] - prefix_sum[x - 1] << '\n';
    }
}
