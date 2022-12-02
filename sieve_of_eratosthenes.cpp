// BOJ 1978 소수 찾기

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 1000005;
bool P[MAX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    fill_n(P, MAX, 1);
    P[0] = P[1] = 0;

    for (int i = 2; i < MAX; i++)
        if (P[i])
            for (int j = i * i; j < MAX; j += i)
                P[j] = 0;
    

    int q, n, ans = 0;
    cin >> q;
    while (q--) {
        cin >> n;
        ans += P[n];
    }
    cout << ans;
}
