// BOJ 16900 이름 정하기

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

vector<int> z(string &s) {
    int n = s.sz;
    int l = 0;
    int r = 0;
    vector<int> ret(n);

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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    ll k;
    cin >> s >> k;

    int n = s.sz;
    vector<int> v = z(s);

    for (int i = 0; i < n; i++) {
        if (v[i] == n - i) {
            cout << (k - 1) * i + n << '\n';
            return 0;
        }
    }

    cout << k * n;
}
