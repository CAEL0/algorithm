// BOJ 17410 수열과 쿼리 1.5

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

    int n;
    cin >> n;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    int k = 1000;
    vector<vector<int>> w(n / k + 5);
    for (int i = 1; i <= n; i++)
        w[(i + k - 1) / k].push_back(v[i]);

    for (int i = 1; i < w.sz; i++)
        sort(w[i].begin(), w[i].end());

    int q;
    cin >> q;

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int i, x;
            cin >> i >> x;

            int j = (i + k - 1) / k;
            w[j].erase(lower_bound(w[j].begin(), w[j].end(), v[i]));
            v[i] = x;
            w[j].insert(upper_bound(w[j].begin(), w[j].end(), x), x);
        } else if (op == 2) {
            int i, j, x;
            cin >> i >> j >> x;

            int ans = 0;
            while (i <= j) {
                if ((i + k - 1) % k == 0 && i + k <= j) {
                    int l = (i + k - 1) / k;
                    ans += w[l].end() - upper_bound(w[l].begin(), w[l].end(), x);
                    i += k;
                } else {
                    if (x < v[i])
                        ans++;

                    i++;
                }
            }

            cout << ans << '\n';
        }
    }
}
