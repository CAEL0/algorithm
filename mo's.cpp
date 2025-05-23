// BOJ 13547 수열과 쿼리 5

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

void add(int j, vector<int> &v, vector<int> &counter, int &cnt) {
    if (counter[v[j]]++ == 0)
        cnt++;
}

void sub(int j, vector<int> &v, vector<int> &counter, int &cnt) {
    if (--counter[v[j]] == 0)
        cnt--;
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

    int k = sqrt(n);
    sort(queries.begin(), queries.end(), [&](auto &x, auto &y) {
        if (x.fi.fi / k != y.fi.fi / k)
            return x.fi.fi / k < y.fi.fi / k;
        return x.fi.se < y.fi.se;
    });

    int s = queries[0].fi.fi;
    int e = s - 1;
    int cnt = 0;
    vector<int> counter(1000005);
    vector<int> ans(q);
    for (int i = 0; i < q; i++) {
        while (queries[i].fi.fi < s)
            add(--s, v, counter, cnt);

        while (e < queries[i].fi.se)
            add(++e, v, counter, cnt);

        while (s < queries[i].fi.fi)
            sub(s++, v, counter, cnt);

        while (queries[i].fi.se < e)
            sub(e--, v, counter, cnt);

        ans[queries[i].se] = cnt;
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

void add(int j, vector<int> &v, vector<int> &counter1, vector<int> &counter2, int &cnt) {
    counter2[counter1[v[j]]]--;
    counter1[v[j]]++;
    counter2[counter1[v[j]]]++;

    if (counter2[cnt + 1] > 0)
        cnt++;
}

void sub(int j, vector<int> &v, vector<int> &counter1, vector<int> &counter2, int &cnt) {
    counter2[counter1[v[j]]]--;
    if (counter2[cnt] == 0)
        cnt--;

    counter1[v[j]]--;
    counter2[counter1[v[j]]]++;
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

    int k = sqrt(n);
    sort(queries.begin(), queries.end(), [&](auto &x, auto &y) {
        if (x.fi.fi / k != y.fi.fi / k)
            return x.fi.fi / k < y.fi.fi / k;
        return x.fi.se < y.fi.se;
    });

    int s = queries[0].fi.fi;
    int e = s - 1;
    int cnt = 0;
    vector<int> counter1(1000005);
    vector<int> counter2(1000005);
    vector<int> ans(q);
    for (int i = 0; i < q; i++) {
        while (queries[i].fi.fi < s)
            add(--s, v, counter1, counter2, cnt);

        while (e < queries[i].fi.se)
            add(++e, v, counter1, counter2, cnt);

        while (s < queries[i].fi.fi)
            sub(s++, v, counter1, counter2, cnt);

        while (queries[i].fi.se < e)
            sub(e--, v, counter1, counter2, cnt);

        ans[queries[i].se] = cnt;
    }

    for (int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}
