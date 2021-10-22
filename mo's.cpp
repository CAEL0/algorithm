#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef tuple<int, int, int> tp;

int n, q;

bool cmp(tp x, tp y) {
    if (get<0>(x) / (int)sqrt(q) < get<0>(y) / (int)sqrt(q))
        return true;
    if (get<0>(x) / (int)sqrt(q) == get<0>(y) / (int)sqrt(q) && get<1>(x) < get<1>(y))
        return true;
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    cin >> q;
    tp query[q];
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        query[i] = tp(a, b, i);
    }
    sort(query, query + q, cmp);
    
    int ans[q] = {0};
    int res[*max_element(arr, arr + n) + 1] = {0};
    int cnt = 0, left, right, idx;
    tie(left, right, idx) = query[0];
    for (int j = left - 1; j < right; j++)
        cnt += (res[arr[j]]++ == 0);
    ans[idx] = cnt;

    for (int i = 1; i < q; i++) {
        int ll, rr;
        tie(ll, rr, idx) = query[i];
        if (right < ll || rr < left) {
            fill_n(res, *max_element(arr, arr + n) + 1, 0);
            cnt = 0;
            for (int j = ll - 1; j < rr; j++)
                cnt += (res[arr[j]]++ == 0);
        } else {
            if (ll < left)
                for (int j = ll - 1; j < left - 1; j++)
                    cnt += (res[arr[j]]++ == 0);
            else
                for (int j = left - 1; j < ll - 1; j++)
                    cnt -= (--res[arr[j]] == 0);
            if (right < rr)
                for (int j = right; j < rr; j++)
                    cnt += (res[arr[j]]++ == 0);
            else
                for (int j = rr; j < right; j++)
                    cnt -= (--res[arr[j]] == 0);
        }
        ans[idx] = cnt;
        left = ll;
        right = rr;
    }
    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}
