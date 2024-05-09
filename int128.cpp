#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

__int128 string_to_int128(string &s) {
    int sign = 1;
    __int128 ret = 0;

    if (s[0] == '-')
        sign = -1;

    for (int i = (sign == -1 ? 1 : 0); i < s.sz; i++) {
        ret *= 10;
        ret += s[i] - '0';
    }

    return ret * sign;
}

void print_int128(__int128 n) {
    if (n == 0) {
        cout << '0' << '\n';
        return;
    }

    if (n < 0) {
        cout << '-';
        n *= -1;
    }

    vector<int> v;
    while (n) {
        v.push_back(n % 10);
        n /= 10;
    }

    for (int i = v.sz - 1; i >= 0; i--)
        cout << v[i];
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        string a, b;
        cin >> a >> b;

        __int128 x = string_to_int128(a);
        __int128 y = string_to_int128(b);

        print_int128(x + y);
    }
}
