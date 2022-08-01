// BOJ 1786 찾기

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

int lps[1000005];
vector<int> ans;

void kmp(string T, string P) {
    int j = 0;
    for (int i = 1; i < P.length(); i++) {
        while (j > 0 && P[i] != P[j])
            j = lps[j - 1];
        
        if (P[i] == P[j])
            lps[i] = ++j;
    }
    j = 0;
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
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string X, Y;
    getline(cin, X);
    getline(cin, Y);
    kmp(X, Y);

    cout << ans.sz << '\n';
    for (int i: ans)
        cout << i << ' ';
}
