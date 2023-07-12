// BOJ 1978 소수 찾기

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 1000005;
bool sieve[MAX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    fill_n(sieve, MAX, true);
    sieve[0] = sieve[1] = false;
    for (int i = 2; i < MAX; i++)
        if (sieve[i])
            for (ll j = (ll)i * i; j < MAX; j += i)
                sieve[j] = false;
    
    int q;
    cin >> q;
    
    int ans = 0;
    while (q--) {
        int n;
        cin >> n;
        ans += sieve[n];
    }
    cout << ans;
}
