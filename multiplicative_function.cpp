#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    // tau[x] := the number of divisors of x
    vector<int> tau(n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; i * j <= n; j++)
            tau[i * j]++;

    // sigma[x] := the sum of divisors of x
    vector<int> sigma(n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; i * j <= n; j++)
            sigma[i * j] += i;

    // phi[x] := the number of integers less than x that are relatively prime to x
    vector<int> phi(n + 1);
    for (int i = 1; i <= n; i++) {
        phi[i] += i;

        for (int j = 2; i * j <= n; j++)
            phi[i * j] -= phi[i];
    }

    // Möbius function
    vector<int> mu(n + 1);
    mu[1] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 2; i * j <= n; j++)
            mu[i * j] -= mu[i];
}
