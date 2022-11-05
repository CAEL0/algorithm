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

using namespace std;
const int MAX = 1000005;
bool p[MAX];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    fill_n(p, MAX, 1);
    p[0] = p[1] = 0;

    for (int i = 2; i < MAX; i++)
        if (p[i])
            for (int j = i * i; j < MAX; j += i)
                p[j] = 0;
    

    int q, n, ans = 0;
    cin >> q;
    while (q--) {
        cin >> n;
        ans += p[n];
    }
    cout << ans;
}
