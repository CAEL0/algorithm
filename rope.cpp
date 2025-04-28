// BOJ 16994 로프와 쿼리

#include <bits/stdc++.h>
#include <ext/rope>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
using namespace __gnu_cxx;
typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    int q;
    cin >> s >> q;

    int n = s.sz;

    crope rope(s.c_str());
    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int x, y;
            cin >> x >> y;

            rope = rope.substr(x, y - x + 1) + rope.substr(0, x) + rope.substr(y + 1, n);
        } else if (op == 2) {
            int x, y;
            cin >> x >> y;

            rope = rope.substr(0, x) + rope.substr(y + 1, n) + rope.substr(x, y - x + 1);
        } else if (op == 3) {
            int x;
            cin >> x;

            cout << rope[x] << '\n';
        }
    }
}
