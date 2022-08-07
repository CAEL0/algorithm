// BOJ 1912 연속합

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int N, A[100005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> A[i];

    int mx = A[0];
    int ans = mx;
    for (int i = 1; i < N; i++) {
        mx = max(mx + A[i], A[i]);
        ans = max(ans, mx);
    }
    cout << ans;
}
