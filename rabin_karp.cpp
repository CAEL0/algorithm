// BOJ 3033 가장 긴 문자열

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MOD = (1 << 19) - 1;

bool compare(int i, int j, int length, string &s) {
    while (length--) {
        if (s[i] != s[j])
            return false;

        i++;
        j++;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    string s;
    cin >> n >> s;

    int base = 31;
    int ans = 0;
    int left = 1;
    int right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;

        ll hash = 0;
        ll k = 1;
        for (int i = 0; i < mid; i++) {
            hash = (hash * base + s[i]) % MOD;
            k = k * base % MOD;
        }

        vector<vector<int>> v(MOD);
        v[hash].push_back(0);

        bool flag = false;
        for (int i = mid; i < n; i++) {
            hash = ((hash * base + s[i] - k * s[i - mid]) % MOD + MOD) % MOD;
            for (int j : v[hash]) {
                if (compare(j, i - mid + 1, mid, s)) {
                    flag = true;
                    break;
                }
            }

            if (flag)
                break;

            v[hash].push_back(i - mid + 1);
        }

        if (flag) {
            ans = max(ans, mid);
            left = mid + 1;
        } else
            right = mid - 1;
    }

    cout << ans;
}
