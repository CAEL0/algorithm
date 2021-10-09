#include <iostream>
#include <bits/stdc++.h>
#define fi first
#define se second
#define sz size()
#define bk back()

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

vector<pll> STK;

double cross(int j, int k) {
    ll x1, y1, x2, y2;
    tie(x1, y1) = STK[j];
    tie(x2, y2) = STK[k];
    return (double)(y2 - y1) / (x1 - x2);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N;
    cin >> N;

    int A[N], B[N];
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> B[i];
    }
    STK.push_back(pll(B[0], 0));
    
    for (int i = 1; i < N; i++) {
        int left = 0;
        int right = STK.sz - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (cross(mid, mid + 1) <= A[i]) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        STK.push_back(pll(B[i], STK[left].fi * A[i] + STK[left].se));
        while (STK.sz > 2 && cross(STK.sz - 2, STK.sz - 1) <= cross(STK.sz - 3, STK.sz - 2)) {
            pll tmp = STK.back();
            STK.pop_back();
            STK.pop_back();
            STK.push_back(tmp);
        }
    }
    cout << STK.bk.se;
}
