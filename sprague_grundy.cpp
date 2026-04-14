// BOJ 13034 다각형 게임

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

    int n;
    cin >> n;

    vector<int> grundy(n + 1);
    for (int i = 2; i <= n; i++) {
        vector<bool> v(i + 1);
        int left = 0;
        int right = i - 2;
        while (left <= right) {
            v[grundy[left] ^ grundy[right]] = true;
            left++;
            right--;
        }

        int mex = 0;
        while (v[mex])
            mex++;

        grundy[i] = mex;
    }

    cout << (grundy[n] == 0 ? 2 : 1);
}
