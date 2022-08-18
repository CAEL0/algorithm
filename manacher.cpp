// BOJ BOJ 13275 가장 긴 팰린드롬 부분 문자열

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second
 
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 200005;
int N, A[MAX];
string S;
char C[MAX];
void manacher() {
    int r = -1, c = -1;
    for (int i = 1; i < N; i++) {
        if (r < i - 1 + A[i - 1]) {
            r = i - 1 + A[i - 1];
            c = i - 1;
        }
        if (r >= i)
            A[i] = min(r - i, A[2 * c - i]);
        
        while (i - A[i] > 0 && i + A[i] < N - 1 && C[i - A[i] - 1] == C[i + A[i] + 1])
            A[i]++;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> S;
    N = 2 * S.length() + 1;
    for (int i = 0; i < N; i++) {
        if (i & 1)
            C[i] = S[i / 2];
        else
            C[i] = '#';
    }
    manacher();
    cout << *max_element(A, A + N);
}
