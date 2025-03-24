// BOJ 30861 Special Numbers

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 1e9 + 7;

vector<int> digits(string &s) {
    vector<int> ret;
    for (char c : s)
        ret.push_back(c - '0');

    reverse(ret.begin(), ret.end());
    return ret;
}

int f(bool partial, bool is_leading, int idx, ll k, vector<int> &digits, vector<vector<unordered_map<ll, int>>> &dp) {
    if (idx == -1)
        return k == 1;

    if (partial) {
        int ret = 0;
        for (int i = 0; i <= digits[idx]; i++) {
            if (i == 0)
                ret = (ret + f(i == digits[idx], is_leading, idx - 1, is_leading ? k : 1, digits, dp)) % MOD;
            else
                ret = (ret + f(i == digits[idx], false, idx - 1, k / gcd(k, (ll)i), digits, dp)) % MOD;
        }

        return ret;
    }

    if (dp[is_leading][idx].count(k))
        return dp[is_leading][idx][k];

    int ret = 0;
    for (int i = 0; i <= 9; i++) {
        if (i == 0)
            ret = (ret + f(false, is_leading, idx - 1, is_leading ? k : 1, digits, dp)) % MOD;
        else
            ret = (ret + f(false, false, idx - 1, k / gcd(k, (ll)i), digits, dp)) % MOD;
    }

    return dp[is_leading][idx][k] = ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll k;
    string l, r;
    cin >> k >> l >> r;

    vector<vector<unordered_map<ll, int>>> dp(2, vector<unordered_map<ll, int>>(22));
    vector<int> v = digits(r);
    vector<int> w = digits(l);
    if (l == "1")
        w.clear();
    else {
        w[0]--;
        for (int i = 0; i < w.sz; i++) {
            if (w[i] == -1) {
                w[i] = 9;
                w[i + 1]--;
            }
        }
        if (w.bk == 0)
            w.pop_back();
    }

    cout << (f(true, true, v.sz - 1, k, v, dp) - f(true, true, w.sz - 1, k, w, dp) + MOD) % MOD;
}
