// BOJ 13263 나무 자르기

#include <iostream>
#include <bits/stdc++.h>
#define fi first
#define se second
#define sz size()
#define bk back()

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

const int MAX = 100005;
int N, A[MAX], B[MAX];
vector<pll> S;

ld cross(int j, int k) {
    auto [x, y] = S[j];
    auto [z, w] = S[k];
    return (ld)(w - y) / (x - z);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;

    for (int i = 0; i < N; i++)
        cin >> A[i];
    
    for (int i = 0; i < N; i++)
        cin >> B[i];
    
    S.push_back(pll(B[0], 0));
    
    for (int i = 1; i < N; i++) {
        int left = 0;
        int right = S.sz - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (cross(mid, mid + 1) <= A[i])
                left = mid + 1;
            else
                right = mid;
        }
        S.push_back(pll(B[i], S[left].fi * A[i] + S[left].se));
        while (S.sz > 2 && cross(S.sz - 2, S.sz - 1) <= cross(S.sz - 3, S.sz - 2))
            S.erase(S.end() - 2);
    }
    cout << S.bk.se;
}
