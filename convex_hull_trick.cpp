#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef pair<long long, long long> pll;

vector<pll> stk;

double cross(int j, int k) {
    long long x1, y1, x2, y2;
    tie(x1, y1) = stk[j];
    tie(x2, y2) = stk[k];
    return (y2 - y1) / (x1 - x2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;

    int tmp, a[n], b[n];
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        a[i] = tmp;
    }
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        b[i] = tmp;
    }

    stk.push_back(pll(b[0], 0));
    
    for (int i = 1; i < n; i++) {
        int left = 0;
        int right = stk.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (cross(mid, mid + 1) <= a[i]) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        stk.push_back(pll(b[i], stk[left].first * a[i] + stk[left].second));
        while (stk.size() > 2 && cross(stk.size() - 2, stk.size() - 1) <= cross(stk.size() - 3, stk.size() - 2)) {
            long long x, y;
            tie(x, y) = stk.back();
            stk.pop_back();
            stk.pop_back();
            stk.push_back(pll(x, y));
        }
    }
    cout << stk.back().second;
}
