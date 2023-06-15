// BOJ 1270 전쟁 - 땅따먹기

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

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<ll> v(n);
        for (int i = 0; i < n; i++)
            cin >> v[i];

        ll k;
        int cnt = 0;
        for (ll &x : v) {
            if (cnt == 0) {
                k = x;
                cnt = 1;
                continue;
            }
            if (x == k)
                cnt++;
            else
                cnt--;
        }
        cnt = 0;
        for (ll &x : v)
            if (x == k)
                cnt++;

        if (cnt > n / 2)
            cout << k << '\n';
        else
            cout << "SYJKGW\n";
    }
}
