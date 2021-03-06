// BOJ 13263 나무 자르기

#include <iostream>
#include <bits/stdc++.h>
#define fi first
#define se second
#define sz size()
#define bk back()

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

vector<pll> stk;

double cross(int j, int k) {
    ll x, y, z, w;
    tie(x, y) = stk[j];
    tie(z, w) = stk[k];
    return (double)(w - y) / (x - z);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;

    int a[n], b[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    
    stk.push_back(pll(b[0], 0));
    
    for (int i = 1; i < n; i++) {
        int left = 0;
        int right = stk.sz - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (cross(mid, mid + 1) <= a[i])
                left = mid + 1;
            else
                right = mid;
        }
        stk.push_back(pll(b[i], stk[left].fi * a[i] + stk[left].se));
        while (stk.sz > 2 && cross(stk.sz - 2, stk.sz - 1) <= cross(stk.sz - 3, stk.sz - 2)) {
            stk.erase(stk.end() - 2);
        }
    }
    cout << stk.bk.se;
}
