// BOJ 1912 연속합

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

    int n;
    cin >> n;
    
    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    int mx = 0;
    int ans = INT_MIN;
    
    for (int i = 0; i < n; i++) {
        mx = max(mx + v[i], v[i]);
        ans = max(ans, mx);
    }
    
    cout << ans;
}
