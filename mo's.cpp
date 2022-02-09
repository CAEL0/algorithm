// BOJ 13547

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
        if (ss < s) add(ss - 1, s - 1);
        else sub(s - 1, ss - 1);
        if (e < ee) add(e, ee);
        else sub(ee, e);
        ans[query[i].idx] = cnt;
        s = ss;
        e = ee;
    }
    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}

//--------------------------------------------------------------------------------

// BOJ 13548

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int MAX = 100010, k = 316;
int cnt, arr[MAX], res1[MAX], res2[MAX], ans[MAX];

struct Query {
    int s, e, idx;
    bool operator < (Query &x) {
        return s / k == x.s / k ? e < x.e: s / k < x.s / k;
    }
};
void add(int j) {
    res2[res1[arr[j]]]--;
    res1[arr[j]]++;
    res2[res1[arr[j]]]++;
    if (res2[cnt + 1] > 0)
        cnt++;
}
void sub(int j) {
    res2[res1[arr[j]]]--;
    if (res2[cnt] == 0)
        cnt--;
    res1[arr[j]]--;
    res2[res1[arr[j]]]++;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, q;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    cin >> q;
    Query qry[q];
    for (int i = 0; i < q; i++) {
        cin >> qry[i].s >> qry[i].e;
        qry[i].idx = i;
    }
    sort(qry, qry + q);
    
    int s = qry[0].s;
    int e = qry[0].e;
    for (int i = s; i <= e; i++)
        add(i);

    ans[qry[0].idx] = cnt;

    for (int i = 1; i < q; i++) {
        while (e < qry[i].e) add(++e);
        while (s > qry[i].s) add(--s);
        while (e > qry[i].e) sub(e--);
        while (s < qry[i].s) sub(s++);
        ans[qry[i].idx] = cnt;
    }
    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}
