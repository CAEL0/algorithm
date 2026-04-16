// BOJ 9483 Tandem Repeats

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

vector<int> z(string s) {
    int n = s.sz;
    int l = 0;
    int r = 0;
    vector<int> ret(n + 1);

    for (int i = 1; i < n; i++) {
        if (i <= r)
            ret[i] = min(r - i, ret[i - l]);

        while (i + ret[i] < n && s[ret[i]] == s[i + ret[i]])
            ret[i]++;

        if (r < i + ret[i] - 1) {
            l = i;
            r = i + ret[i] - 1;
        }
    }

    return ret;
}

ll main_lorentz(string &s) {
    if (s.sz == 1)
        return 0;

    int n = s.sz / 2;
    int m = s.sz - n;

    string x = s.substr(0, n);
    string y = s.substr(n);

    string xx(x.rbegin(), x.rend());
    string yy(y.rbegin(), y.rend());

    ll ret = main_lorentz(x) + main_lorentz(y);

    vector<int> zxx = z(xx);
    vector<int> zyx = z(y + '#' + x);
    for (int len = 1; len <= n; len++) {
        int p = zxx[len];
        int q = zyx[m + 1 + n - len];
        if (p > 0 && q > 0 && p + q >= len)
            ret += min(p, len - 1) - max(1, len - q) + 1;
    }

    vector<int> zxxyy = z(xx + '#' + yy);
    vector<int> zy = z(y);
    for (int len = 1; len <= m; len++) {
        int p = zxxyy[n + 1 + m - len];
        int q = zy[len];
        if (p > 0 && p + q >= len)
            ret += min(p, len) - max(1, len - q) + 1;
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    while (1) {
        string s;
        cin >> s;

        if (s == "0")
            break;

        cout << main_lorentz(s) << '\n';
    }
}
