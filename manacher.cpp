// BOJ 13275 가장 긴 팰린드롬 부분 문자열

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

vector<int> manacher(string &s) {
    int n = 2 * s.sz + 1;
    vector<char> w(n);
    for (int i = 0; i < n; i++) {
        if (i & 1)
            w[i] = s[i / 2];
        else
            w[i] = '#';
    }

    int r = -1;
    int c = -1;
    vector<int> ret(n);
    for (int i = 1; i < n; i++) {
        if (r < i - 1 + ret[i - 1]) {
            r = i - 1 + ret[i - 1];
            c = i - 1;
        }

        if (i <= r)
            ret[i] = min(r - i, ret[2 * c - i]);

        while (0 < i - ret[i] && i + ret[i] < n - 1 && w[i - ret[i] - 1] == w[i + ret[i] + 1])
            ret[i]++;
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;

    vector<int> v = manacher(s);

    cout << *max_element(v.begin(), v.end());
}
