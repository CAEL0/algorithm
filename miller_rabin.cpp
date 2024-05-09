// BOJ 5615 아파트 임대

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

ll ipow(ll base, ll exp, ll mod) {
    ll ret = 1;
    base %= mod;

    while (exp) {
        if (exp & 1)
            ret = (__int128)ret * base % mod;

        exp >>= 1;
        base = (__int128)base * base % mod;
    }

    return ret;
}

bool miller_rabin(ll x) {
    if (x == 1)
        return false;

    int s = 0;
    ll d = x - 1;

    while (!(d & 1)) {
        s++;
        d >>= 1;
    }

    for (ll a : {2, 7, 61}) {
        if (a >= x - 1)
            break;

        ll b = ipow(a, d, x);
        if (b == 1 || b == x - 1)
            continue;

        if (s == 1)
            return false;

        bool flag = true;
        for (int i = 0; i < s - 1; i++) {
            b = (__int128)b * b % x;

            if (b == x - 1) {
                flag = false;
                break;
            }
        }

        if (flag)
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int q;
    cin >> q;

    int ans = 0;

    while (q--) {
        ll x;
        cin >> x;

        ans += miller_rabin(2 * x + 1);
    }

    cout << ans;
}

//--------------------------------------------------------------------------------

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

ll ipow(ll base, ll exp, ll mod) {
    ll ret = 1;
    base %= mod;

    while (exp) {
        if (exp & 1)
            ret = (__int128)ret * base % mod;

        exp >>= 1;
        base = (__int128)base * base % mod;
    }

    return ret;
}

bool miller_rabin(ll x) {
    if (x == 1)
        return false;

    int s = 0;
    ll d = x - 1;

    while (!(d & 1)) {
        s++;
        d >>= 1;
    }

    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23}) {
        if (a >= x - 1)
            break;

        ll b = ipow(a, d, x);
        if (b == 1 || b == x - 1)
            continue;

        if (s == 1)
            return false;

        bool flag = true;
        for (int i = 0; i < s - 1; i++) {
            b = (__int128)b * b % x;

            if (b == x - 1) {
                flag = false;
                break;
            }
        }

        if (flag)
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int q;
    cin >> q;

    while (q--) {
        ll x;
        cin >> x;

        cout << (miller_rabin(x) ? "Yes" : "No") << '\n';
    }
}
