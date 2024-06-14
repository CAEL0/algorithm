// BOJ 15106 Fear Factoring

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

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

__int128 f(__int128 n) {
    __int128 ret = 0;
    __int128 s = 1;
    __int128 e = 1;

    while (1) {
        __int128 a = n / s;
        ret += a * (e - s + 1) * (s + e) / 2;

        if (a <= 1)
            break;

        s = e + 1;
        e = n / (n / s);
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll a, b;
    cin >> a >> b;

    print_int128(f(b) - f(a - 1));
}
