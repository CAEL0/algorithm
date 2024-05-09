// BOJ 15965 K번째 소수

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

    vector<bool> sieve(10000005, true);
    sieve[0] = sieve[1] = false;

    for (int i = 2; i < sieve.sz; i++)
        if (sieve[i])
            for (ll j = (ll)i * i; j < sieve.sz; j += i)
                sieve[j] = false;

    int k;
    cin >> k;

    for (int i = 0; i < sieve.sz; i++) {
        if (!sieve[i])
            continue;

        if (--k == 0) {
            cout << i;
            return 0;
        }
    }
}
