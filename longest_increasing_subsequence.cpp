// BOJ 14003 가장 긴 증가하는 부분 수열 5

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

vector<int> lis(vector<int> &v) {
    int n = v.sz;
    vector<int> dp(n, 1);
    vector<int> w = {v[0]};
    for (int i = 1; i < n; i++) {
        if (v[i] > w.bk) {
            w.push_back(v[i]);
            dp[i] = w.sz;
        } else {
            int j = lower_bound(w.begin(), w.end(), v[i]) - w.begin();
            dp[i] = j + 1;
            w[j] = min(w[j], v[i]);
        }
    }

    vector<int> ret;
    int i = n;
    int j = w.sz;
    while (j) {
        if (dp[--i] == j) {
            ret.push_back(v[i]);
            j--;
        }
    }
    reverse(ret.begin(), ret.end());

    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    vector<int> ans = lis(v);

    cout << ans.sz << '\n';
    for (int x : ans)
        cout << x << ' ';
}
