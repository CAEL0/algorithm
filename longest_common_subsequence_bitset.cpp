// BOJ 18439 LCS 6

#define private public
#include <bitset>
#undef private

#include <bits/stdc++.h>
#include <x86intrin.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

template <size_t _Nw> void _M_do_sub(_Base_bitset<_Nw> &A, const _Base_bitset<_Nw> &B) {
    for (int i = 0, c = 0; i < _Nw; i++)
        c = _subborrow_u64(c, A._M_w[i], B._M_w[i], (unsigned long long *)&A._M_w[i]);
}
template <> void _M_do_sub(_Base_bitset<1> &A, const _Base_bitset<1> &B) { A._M_w -= B._M_w; }
template <size_t _Nb> bitset<_Nb> &operator-=(bitset<_Nb> &A, const bitset<_Nb> &B) { return _M_do_sub(A, B), A; }
template <size_t _Nb> inline bitset<_Nb> operator-(const bitset<_Nb> &A, const bitset<_Nb> &B) {
    bitset<_Nb> C(A);
    return C -= B;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string x, y;
    cin >> x >> y;

    vector<bitset<50000>> v(26);
    for (int j = 0; j < y.sz; j++)
        v[y[j] - 'A'].set(j);

    bitset<50000> bs1;
    for (int i = 0; i < x.sz; i++) {
        bitset<50000> bs2 = bs1 | v[x[i] - 'A'];
        bs1 <<= 1;
        bs1.set(0);
        bs1 = ((bs2 - bs1) ^ bs2) & bs2;
    }

    cout << bs1.count();
}
