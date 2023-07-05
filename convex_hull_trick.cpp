// BOJ 13263 나무 자르기

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
int n, a[MAX], b[MAX];
vector<pll> stk;

ld cross(int i, int j) {
    auto [x, y] = stk[i];
    auto [z, w] = stk[j];
    return (ld)(w - y) / (x - z);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++)
        cin >> b[i];

    stk.push_back(pll(b[0], 0));

    for (int i = 1; i < n; i++) {
        while (2 < stk.sz &&
               cross(stk.sz - 2, stk.sz - 1) <= cross(stk.sz - 3, stk.sz - 2))
            stk.erase(stk.end() - 2);
        
        int left = 0;
        int right = stk.sz - 2;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (cross(mid, mid + 1) <= a[i])
                left = mid + 1;
            else
                right = mid - 1;
        }
        stk.push_back(pll(b[i], stk[left].fi * a[i] + stk[left].se));
    }
    cout << stk.bk.se;
}

//--------------------------------------------------------------------------------

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
int n, a[MAX], b[MAX];
vector<pll> stk;

ld cross(int i, int j) {
    auto [x, y] = stk[i];
    auto [z, w] = stk[j];
    return (ld)(w - y) / (x - z);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 0; i < n; i++)
        cin >> b[i];

    stk.push_back(pll(b[0], 0));

    int idx = 0;
    for (int i = 1; i < n; i++) {
        while (2 < stk.sz &&
               cross(stk.sz - 2, stk.sz - 1) <= cross(stk.sz - 3, stk.sz - 2))
            stk.erase(stk.end() - 2);

        while (idx + 1 < stk.sz && cross(idx, idx + 1) <= a[i])
            idx++;

        stk.push_back(pll(b[i], stk[idx].fi * a[i] + stk[idx].se));
    }
    cout << stk.bk.se;
}
