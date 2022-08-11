// BOJ 9248 Suffix Array

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 500005;
int N, d, sa[MAX], pos[MAX], tmp[MAX], lcp[MAX];
string S;

bool cmp(int i, int j) {
    if (pos[i] != pos[j])
        return pos[i] < pos[j];
    
    i += d;
    j += d;
    return (i < N && j < N) ? (pos[i] < pos[j]) : (i > j);
}
void SA() {
    N = S.length();
    for (int i = 0; i < N; i++) {
        sa[i] = i;
        pos[i] = S[i];
    }
    d = 1;
    while (1) {
        sort(sa, sa + N, cmp);
        fill_n(tmp, N, 0);
        for (int i = 0; i < N - 1; i++)
            tmp[i + 1] = tmp[i] + cmp(sa[i], sa[i + 1]);
        
        for (int i = 0; i < N; i++)
            pos[sa[i]] = tmp[i];
        
        if (tmp[N - 1] == N - 1)
            break;
        
        d *= 2;
    }
}
void LCP() {
    int k = 0;
    for (int i = 0; i < N; i++) {
        if (!pos[i]) {
            k = max(k - 1, 0);
            continue;
        }
        int j = sa[pos[i] - 1];
        while (max(i, j) + k < N && S[i + k] == S[j + k])
            k++;
        
        lcp[pos[i]] = k;
        k = max(k - 1, 0);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> S;
    SA();
    LCP();
    for (int i = 0; i < N; i++)
        cout << sa[i] + 1 << ' ';
    cout << '\n';
    cout << "x ";
    for (int i = 1; i < N; i++)
        cout << lcp[i] << ' ';
}

//--------------------------------------------------------------------------------

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    string s;
    cin >> s;
    int n = s.length();

    int sa[n], pos[n + 1], d = 1, k = max(n, 200);
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        pos[i] = (int)s[i];
    }
    pos[n] = 0;
    
    int cnt[k], idx[n], tmp[n];
    while (true) {
        fill_n(cnt, k, 0);
        fill_n(idx, n, 0);
        fill_n(tmp, n, 0);

        cnt[0] = d;
        for (int i = d; i < n; i++)
            cnt[pos[i]]++;
        
        for (int i = 1; i < k; i++)
            cnt[i] += cnt[i - 1];
        
        for (int i = n - 1; i > -1; i--) {
            cnt[pos[min(i + d, n)]]--;
            idx[cnt[pos[min(i + d, n)]]] = i;
        }
        fill_n(cnt, k, 0);
        for (int i = 0; i < n; i++)
            cnt[pos[i]]++;

        for (int i = 1; i < k; i++)
            cnt[i] += cnt[i - 1];
        
        for (int i = n - 1; i > -1; i--) {
            cnt[pos[idx[i]]]--;
            sa[cnt[pos[idx[i]]]] = idx[i];
        }
        for (int i = 0; i < n - 1; i++) {
            int x = sa[i];
            int y = sa[i + 1];
            if (pos[x] < pos[y] || (pos[x] == pos[y] && pos[min(x + d, n)] < pos[min(y + d, n)]))
                tmp[i + 1] = tmp[i] + 1;
            else
                tmp[i + 1] = tmp[i];
        }
        for (int i = 0; i < n; i++)
            pos[sa[i]] = tmp[i] + 1;
        
        if (tmp[n - 1] == n - 1)
            break;
        
        d *= 2;
    }
    for (int i = 0; i < n; i++)
        cout << sa[i] + 1 << ' ';
    
    cout << '\n';
    int lcp[n], j, z = 0;
    fill_n(lcp, n, 0);
    for (int i = 0; i < n; i++) {
        if (pos[i] == 1) {
            if (z > 0)
                z -= 1;
            continue;
        }
        j = sa[pos[i] - 2];
        while (max(i, j) + z < n && s[i + z] == s[j + z])
            z++;
        
        lcp[pos[i] - 1] = z;
        if (z > 0)
            z--;
    }
    cout << "x ";
    for (int i = 1; i < n; i++)
        cout << lcp[i] << ' ';
}
