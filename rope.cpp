// BOJ 16994 로프와 쿼리

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

#include <ext/rope>
using namespace __gnu_cxx;
crope R;
string S;
int N, Q;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> S >> Q;
    R.append(S.c_str());
    N = S.sz;
    while (Q--) {
        int q;
        cin >> q;
        if (q == 1) {
            int x, y;
            cin >> x >> y;
            R = R.substr(x, y - x + 1) + R.substr(0, x) + R.substr(y + 1, N);
        } else if (q == 2) {
            int x, y;
            cin >> x >> y;
            R = R.substr(0, x) + R.substr(y + 1, N) + R.substr(x, y - x + 1);
        } else {
            int x;
            cin >> x;
            cout << R[x] << '\n';
        }
    }
}
