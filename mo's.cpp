// BOJ 13547 수열과 쿼리 5

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

void add(int s, int e, vector<int> &v, vector<int> &w, int &cnt) {
    for (int j = s; j < e; j++) {
        if (w[v[j]] == 0)
            cnt++;

        w[v[j]]++;
    }
}

void sub(int s, int e, vector<int> &v, vector<int> &w, int &cnt) {
    for (int j = s; j < e; j++) {
        if (w[v[j]] == 1)
            cnt--;

        w[v[j]]--;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i];

    int q;
    cin >> q;

    vector<pair<pii, int>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].fi.fi >> queries[i].fi.se;

        queries[i].se = i;
    }

    int k = sqrt(q);
    sort(queries.begin(), queries.end(), [&](auto &x, auto &y) {
        if (x.fi.fi / k != y.fi.fi / k)
            return x.fi.fi / k < y.fi.fi / k;
        return x.fi.se < y.fi.se;
    });

    vector<int> w(1000005);
    int s = queries[0].fi.fi;
    int e = queries[0].fi.se;
    int cnt = 0;

    add(s - 1, e, v, w, cnt);

    vector<int> ans(q);
    ans[queries[0].se] = cnt;

    for (int i = 1; i < q; i++) {
        int ss = queries[i].fi.fi;
        int ee = queries[i].fi.se;

        if (ss < s)
            add(ss - 1, s - 1, v, w, cnt);
        else
            sub(s - 1, ss - 1, v, w, cnt);

        if (e < ee)
            add(e, ee, v, w, cnt);
        else
            sub(ee, e, v, w, cnt);

        ans[queries[i].se] = cnt;
        s = ss;
        e = ee;
    }

    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}

//--------------------------------------------------------------------------------

// BOJ 13548 수열과 쿼리 6

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

void add(int j, vector<int> &v, vector<int> &w, vector<int> &u, int &cnt) {
    u[w[v[j]]]--;
    w[v[j]]++;
    u[w[v[j]]]++;

    if (u[cnt + 1] > 0)
        cnt++;
}

void sub(int j, vector<int> &v, vector<int> &w, vector<int> &u, int &cnt) {
    u[w[v[j]]]--;
    if (u[cnt] == 0)
        cnt--;

    w[v[j]]--;
    u[w[v[j]]]++;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> v[i];

    int q;
    cin >> q;

    vector<pair<pii, int>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].fi.fi >> queries[i].fi.se;

        queries[i].se = i;
    }

    int k = sqrt(q);
    sort(queries.begin(), queries.end(), [&](auto &x, auto &y) {
        if (x.fi.fi / k != y.fi.fi / k)
            return x.fi.fi / k < y.fi.fi / k;
        return x.fi.se < y.fi.se;
    });

    vector<int> w(1000005);
    vector<int> u(1000005);
    int s = queries[0].fi.fi;
    int e = queries[0].fi.se;
    int cnt = 0;

    for (int i = s; i <= e; i++)
        add(i, v, w, u, cnt);

    vector<int> ans(q);
    ans[queries[0].se] = cnt;

    for (int i = 1; i < q; i++) {
        while (e < queries[i].fi.se)
            add(++e, v, w, u, cnt);

        while (s > queries[i].fi.fi)
            add(--s, v, w, u, cnt);

        while (e > queries[i].fi.se)
            sub(e--, v, w, u, cnt);

        while (s < queries[i].fi.fi)
            sub(s++, v, w, u, cnt);

        ans[queries[i].se] = cnt;
    }

    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}
