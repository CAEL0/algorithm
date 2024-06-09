// BOJ 20501 Facebook

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

    vector<bitset<2000>> v(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        v[i] = bitset<2000>(s);
    }

    int q;
    cin >> q;

    while (q--) {
        int x, y;
        cin >> x >> y;

        cout << (v[x - 1] & v[y - 1]).count() << '\n';
    }
}
