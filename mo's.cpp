#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int q, k, cnt;
int arr[100000], res[1000001], ans[100000];

struct Query {
    int s, e, idx;
    bool operator < (Query &x) {
        if (s / k != x.s / k) return s / k < x.s / k;
        return e < x.e;
    }
};
void add(int s, int e) {
    for (int j = s; j < e; j++)
        cnt += (res[arr[j]]++ == 0);
}
void sub(int s, int e) {
    for (int j = s; j < e; j++)
        cnt -= (--res[arr[j]] == 0);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    cin >> q;
    k = sqrt(q);
    Query query[q];
    for (int i = 0; i < q; i++) {
        cin >> query[i].s >> query[i].e;
        query[i].idx = i;
    }
    sort(query, query + q);
    
    int s = query[0].s;
    int e = query[0].e;
    int idx = query[0].idx;
    add(s - 1, e);
    ans[idx] = cnt;

    for (int i = 1; i < q; i++) {
        int ss = query[i].s;
        int ee = query[i].e;
        if (e < ss || ee < s) {
            fill_n(res, *max_element(arr, arr + n) + 1, 0);
            cnt = 0;
            add(ss - 1, ee);
        } else {
            if (ss < s) add(ss - 1, s - 1);
            else sub(s - 1, ss - 1);
            if (e < ee) add(e, ee);
            else sub(ee, e);
        }
        ans[query[i].idx] = cnt;
        s = ss;
        e = ee;
    }
    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}
