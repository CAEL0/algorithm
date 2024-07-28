// BOJ 1144 싼 비용

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

bool is_valid(string &state) {
    set<char> s(state.begin(), state.end());
    s.erase('0');
    return s.sz <= 1;
}

void normalize(string &state) {
    unordered_map<char, char> mp;
    char idx = '1';

    for (char &c : state) {
        if (c == '0')
            continue;

        if (mp.count(c)) {
            c = mp[c];
            continue;
        }

        mp[c] = idx;
        c = idx++;
    }
}

bool pass(int i, int j, string &state, int m) {
    if (state[j] == '0')
        return true;

    for (int k = 0; k < m; k++)
        if (k != j && state[k] == state[j])
            return true;

    return false;
}

int f(int i, int j, string state, vector<vector<int>> &v, vector<vector<unordered_map<string, int>>> &dp, int n, int m) {
    if (i == n)
        return is_valid(state) ? 0 : 1e9;

    normalize(state);

    auto it = dp[i][j].find(state);
    if (it != dp[i][j].end())
        return it->second;

    int ii = i + (j == m - 1);
    int jj = (j + 1) % m;
    int ret = 1e9;
    string original = state;

    if (pass(i, j, state, m)) {
        state[j] = '0';
        ret = min(ret, f(ii, jj, state, v, dp, n, m));
        state = original;
    }

    if (state[j] == '0' && (j == 0 || state[j - 1] == '0')) {
        state[j] = '9';
        ret = min(ret, v[i][j] + f(ii, jj, state, v, dp, n, m));
    } else if (state[j] == '0' && j > 0) {
        state[j] = state[j - 1];
        ret = min(ret, v[i][j] + f(ii, jj, state, v, dp, n, m));
    } else if (j == 0 || state[j - 1] == '0' || state[j - 1] == state[j])
        ret = min(ret, v[i][j] + f(ii, jj, state, v, dp, n, m));
    else {
        char change = state[j - 1];
        for (int k = 0; k < m; k++)
            if (state[k] == change)
                state[k] = state[j];

        ret = min(ret, v[i][j] + f(ii, jj, state, v, dp, n, m));
    }

    if (is_valid(original))
        ret = min(ret, 0);

    return dp[i][j][original] = ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> v(10, vector<int>(10));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> v[i][j];

    vector<vector<unordered_map<string, int>>> dp(10, vector<unordered_map<string, int>>(10));

    cout << f(0, 0, string(m, '0'), v, dp, n, m);
}
