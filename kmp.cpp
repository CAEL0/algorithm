// BOJ 1786 찾기

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int lps[1000005];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string T, P;
    getline(cin, T);
    getline(cin, P);
    
    int j = 0;
    for (int i = 1; i < P.length(); i++) {
        while (j > 0 && P[i] != P[j])
            j = lps[j - 1];
        
        if (P[i] == P[j])
            lps[i] = ++j;
    }
    j = 0;
    vector<int> ans;
    for (int i = 0; i < T.length(); i++) {
        while (j > 0 && T[i] != P[j])
            j = lps[j - 1];
        
        if (T[i] == P[j]) {
            if (j == P.length() - 1) {
                ans.push_back(i - P.length() + 2);
                j = lps[j];
            } else
                j++;
        }
    }
    cout << ans.size() << '\n';
    for (int i: ans)
        cout << i << ' ';
}
