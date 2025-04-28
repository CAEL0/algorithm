// BOJ 2803 내가 어렸을 때 가지고 놀던 장난감

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 1e9 + 7;

ll ipow(ll base, ll exp) {
    ll ret = 1;
    while (exp) {
        if (exp & 1)
            ret = ret * base % MOD;

        exp >>= 1;
        base = base * base % MOD;
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> dp(1 << m);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;

        int mask = 0;
        while (k--) {
            int x;
            cin >> x;

            mask |= (1 << (x - 1));
        }

        dp[mask]++;
    }

    for (int i = 0; i < m; i++)
        for (int x = 0; x < (1 << m); x++)
            if (x & (1 << i))
                dp[x] += dp[x ^ (1 << i)];

    int mask = (1 << m) - 1;
    ll ans = 0;
    for (int x = 0; x < (1 << m); x++) {
        int cnt = __builtin_popcount(x);
        if (cnt & 1)
            ans = (ans - ipow(2, dp[x ^ mask]) + MOD) % MOD;
        else
            ans = (ans + ipow(2, dp[x ^ mask])) % MOD;
    }

    cout << ans;
}

//--------------------------------------------------------------------------------

// BOJ 18719 Binomial

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

    vector<vector<int>> dp(21, vector<int>(1 << 20));

    int t;
    cin >> t;

    while (t--) {
        for (int i = 0; i < 21; i++)
            fill(dp[i].begin(), dp[i].end(), 0);

        int n;
        cin >> n;

        while (n--) {
            int x;
            cin >> x;

            dp[0][x]++;
        }

        for (int x = 0; x < (1 << 20); x++) {
            for (int i = 1; i <= 20; i++) {
                dp[i][x] = dp[i - 1][x];
                if (x & (1 << (i - 1)))
                    dp[i][x] += dp[i - 1][x ^ (1 << (i - 1))];
            }
        }

        ll ans = 0;
        for (int x = 0; x < (1 << 20); x++)
            ans += (ll)dp[0][x] * dp[20][x];

        cout << ans << '\n';
    }
}
