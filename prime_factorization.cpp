// BOJ 16563 어려운 소인수분해

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

vector<int> get_sieve(int n) {
    vector<int> sieve(n + 1, -1);

    for (int i = 2; i <= n; i++)
        if (sieve[i] == -1)
            for (ll j = (ll)i * i; j <= n; j += i)
                if (sieve[j] == -1)
                    sieve[j] = i;

    return sieve;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<int> sieve = get_sieve(5000000);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        while (sieve[n] != -1) {
            cout << sieve[n] << ' ';

            n /= sieve[n];
        }
        if (n > 1)
            cout << n;

        cout << '\n';
    }
}
