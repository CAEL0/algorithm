// BOJ 1786 찾기

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

vector<int> kmp(string &x, string &y) {
    vector<int> lps(y.sz);
    int j = 0;
    for (int i = 1; i < y.sz; i++) {
        while (j > 0 && y[i] != y[j])
            j = lps[j - 1];

        if (y[i] == y[j])
            lps[i] = ++j;
    }

    vector<int> ret;
    j = 0;
    for (int i = 0; i < x.sz; i++) {
        while (j > 0 && x[i] != y[j])
            j = lps[j - 1];

        if (x[i] != y[j])
            continue;

        if (j + 1 == y.sz) {
            ret.push_back(i - y.sz + 2);
            j = lps[j];
        } else
            j++;
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string x, y;
    getline(cin, x);
    getline(cin, y);

    vector<int> ans = kmp(x, y);

    cout << ans.sz << '\n';
    for (int i : ans)
        cout << i << ' ';
}
