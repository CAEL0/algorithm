// BOJ 18438 LCS 5

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

string f(int a, int b, int c, int d, string &x, string &y) {
    if (a > b || c > d)
        return "";

    if (a == b) {
        for (int j = c; j <= d; j++)
            if (x[a] == y[j])
                return x.substr(a, 1);
        return "";
    }

    int mid = (a + b) / 2;

    vector<vector<int>> dp1(2, vector<int>(d - c + 3));
    for (int i = a; i <= mid; i++) {
        int cur = i & 1;
        int prv = cur ^ 1;
        fill(dp1[cur].begin(), dp1[cur].end(), 0);

        for (int j = c; j <= d; j++) {
            if (x[i] == y[j])
                dp1[cur][j - c + 1] = dp1[prv][j - c] + 1;
            else
                dp1[cur][j - c + 1] = max(dp1[prv][j - c + 1], dp1[cur][j - c]);
        }
    }

    vector<vector<int>> dp2(2, vector<int>(d - c + 3));
    for (int i = b; i >= mid + 1; i--) {
        int cur = i & 1;
        int prv = cur ^ 1;
        fill(dp2[cur].begin(), dp2[cur].end(), 0);

        for (int j = d; j >= c; j--) {
            if (x[i] == y[j])
                dp2[cur][j - c + 1] = dp2[prv][j - c + 2] + 1;
            else
                dp2[cur][j - c + 1] = max(dp2[prv][j - c + 1], dp2[cur][j - c + 2]);
        }
    }

    int mx = -1;
    int idx = -1;
    for (int j = c - 1; j <= d; j++) {
        if (mx < dp1[mid & 1][j - c + 1] + dp2[(mid + 1) & 1][j - c + 2]) {
            mx = dp1[mid & 1][j - c + 1] + dp2[(mid + 1) & 1][j - c + 2];
            idx = j;
        }
    }

    return f(a, mid, c, idx, x, y) + f(mid + 1, b, idx + 1, d, x, y);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string x, y;
    cin >> x >> y;

    string ans = f(0, x.sz - 1, 0, y.sz - 1, x, y);

    cout << ans.sz << '\n' << ans;
}
