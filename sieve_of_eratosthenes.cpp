// BOJ 15965 K번째 소수

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

vector<bool> get_sieve(int n) {
    vector<bool> sieve(n, true);
    sieve[0] = sieve[1] = false;

    for (int i = 2; i < n; i++)
        if (sieve[i])
            for (ll j = (ll)i * i; j < n; j += i)
                sieve[j] = false;
    
    return sieve;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<bool> sieve = get_sieve(10000005);

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
