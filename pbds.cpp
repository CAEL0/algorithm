// BOJ 1572 중앙값

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>

void m_erase(ordered_set &os, int x) {
    int idx = os.order_of_key(x);
    auto it = os.find_by_order(idx);
    os.erase(it);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    int m = (k - 1) / 2;
    ll ans = 0;
    ordered_set os;

    for (int i = 1; i <= n; i++) {
        os.insert(v[i]);

        if (i >= k) {
            ans += *os.find_by_order(m);
            m_erase(os, v[i - k + 1]);
        }
    }

    cout << ans;
}
