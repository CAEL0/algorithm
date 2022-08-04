// BOJ 8986 전봇대

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int N, X[100005];

ll f(int k) {
    ll ret = 0;
    ll x = k;
    for (int i = 1; i < N; i++) {
        ret += abs(X[i] - x);
        x += k;
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> X[i];
    
    int left = 0;
    int right = 1e9;
    while (left + 3 < right) {
        int x1 = ((ll)2 * left + right) / 3;
        int x2 = ((ll)left + 2 * right) / 3;
        ll y1 = f(x1);
        ll y2 = f(x2);
        if (y1 >= y2)
            left = x1;
        else
            right = x2;
    }
    ll ans = f(left);
    for (int x = left + 1; x <= right; x++)
        ans = min(ans, f(x));
    
    cout << ans;
}
