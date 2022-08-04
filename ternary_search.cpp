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
    int right = X[N - 1];
    while (left + 3 <= right) {
        int p = ((ll)2 * left + right) / 3;
        int q = ((ll)left + 2 * right) / 3;
        
        if (f(p) >= f(q))
            left = p;
        else
            right = q;
    }
    ll ans = f(left);
    for (int x = left + 1; x <= right; x++)
        ans = min(ans, f(x));
    
    cout << ans;
}
