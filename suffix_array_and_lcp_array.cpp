// BOJ 9248

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

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
