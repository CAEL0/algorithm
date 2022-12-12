// BOJ 10562 나이트

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 1e9 + 9;

ll ipow(ll base, ll exp) {
	ll res = 1;
	while (exp) {
		if (exp & 1)
            res = res * base % MOD;
		base = base * base % MOD;
		exp >>= 1;
	}
	return res;
}
vector<int> berlekamp_massey(vector<int> x) {
	vector<int> ls, cur;
	int lf, ld;
	for (int i = 0; i < x.sz; i++) {
		ll t = 0;
		for (int j = 0; j < cur.sz; j++)
			t = (t + (ll)x[i - j - 1] * cur[j]) % MOD;
		
		if ((t - x[i]) % MOD == 0)
            continue;
		if (cur.empty()) {
			cur.resize(i + 1);
			lf = i;
			ld = (t - x[i]) % MOD;
			continue;
		}
		ll k = (t - x[i]) * ipow(ld, MOD - 2) % MOD;
		vector<int> c(i - lf - 1);
		c.push_back(k);
		for (auto &j: ls)
            c.push_back(-j * k % MOD);
		if (c.sz < cur.sz)
            c.resize(cur.sz);
		for (int j = 0; j < cur.sz; j++)
			c[j] = (c[j] + cur[j]) % MOD;
		if (i - lf + (int)ls.sz >= (int)cur.sz)
			tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % MOD);
		cur = c;
	}
	for (auto &i: cur)
        i = (i % MOD + MOD) % MOD;
	return cur;
}
int get_nth(vector<int> rec, vector<int> dp, ll n){
	int m = rec.sz;
	vector<int> s(m), t(m);
	s[0] = 1;
	if (m != 1)
        t[1] = 1;
	else
        t[0] = rec[0];
    
	auto mul = [&rec](vector<int> v, vector<int> w) {
		int m = v.sz;
		vector<int> t(2 * m);
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < m; k++) {
				t[j + k] += (ll)v[j] * w[k] % MOD;
				if (t[j + k] >= MOD)
                    t[j + k] -= MOD;
			}
		}
		for (int j = 2 * m - 1; j >= m; j--) {
			for (int k = 1; k <= m; k++) {
				t[j - k] += (ll)t[j] * rec[k - 1] % MOD;
				if (t[j - k] >= MOD)
                    t[j - k] -= MOD;
			}
		}
		t.resize(m);
		return t;
	};
	while (n) {
		if (n & 1)
            s = mul(s, t);
		t = mul(t, t);
		n >>= 1;
	}
	ll res = 0;
	for (int i = 0; i < m; i++)
        res = (res + (ll)s[i] * dp[i] % MOD) % MOD;
	return res;
}
int guess_nth_term(vector<int> v, vector<int> x, ll n) {
	if (n < x.sz)
        return x[n];
	return get_nth(v, x, n);
}
int N, M, dp2[105][16], dp3[105][64], dp4[105][256];
vector<int> v2, v3, v4, bm2, bm3, bm4;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    for (int i = 0; i < 16; i++)
        dp2[2][i] = 1;
    
    for (int n = 3; n < 100; n++) {
        for (int i = 0; i < 16; i++) {
            ll res = 0;
            for (int j = 0; j < 16; j++) {
                if ((i & 1) && (j & 8)) continue;
                if ((i & 2) && (j & 4)) continue;
                if (!(i & 4) != !(j & 1)) continue;
                if (!(i & 8) != !(j & 2)) continue;
                res += dp2[n - 1][j];
            }
            dp2[n][i] = res % MOD;
        }
    }
    for (int i = 0; i < 64; i++) {
        if ((i & 1) && (i & 32)) continue;
        if ((i & 4) && (i & 8)) continue;
        dp3[2][i] = 1;
    }
    for (int n = 3; n < 100; n++) {
        for (int i = 0; i < 64; i++) {
            if ((i & 1) && (i & 32)) continue;
            if ((i & 4) && (i & 8)) continue;
            
            ll res = 0;
            for (int j = 0; j < 64; j++) {
                if ((i & 1) && (j & 16)) continue;
                if ((i & 2) && (j & 8)) continue;
                if ((i & 2) && (j & 32)) continue;
                if ((i & 4) && (j & 16)) continue;
                if ((i & 8) && (j & 32)) continue;
                if ((i & 32) && (j & 8)) continue;
                if (!(i & 8) != !(j & 1)) continue;
                if (!(i & 16) != !(j & 2)) continue;
                if (!(i & 32) != !(j & 4)) continue;
                res += dp3[n - 1][j];
            }
            dp3[n][i] = res % MOD;
        }
    }
    for (int i = 0; i < 256; i++) {
        if ((i & 1) && (i & 64)) continue;
        if ((i & 2) && (i & 128)) continue;
        if ((i & 4) && (i & 16)) continue;
        if ((i & 8) && (i & 32)) continue;
        dp4[2][i] = 1;
    }
    for (int n = 3; n < 100; n++) {
        for (int i = 0; i < 256; i++) {
            if ((i & 1) && (i & 64)) continue;
            if ((i & 2) && (i & 128)) continue;
            if ((i & 4) && (i & 16)) continue;
            if ((i & 8) && (i & 32)) continue;
            
            ll res = 0;
            for (int j = 0; j < 256; j++) {
                if ((i & 1) && (j & 32)) continue;
                if ((i & 2) && (j & 16)) continue;
                if ((i & 2) && (j & 64)) continue;
                if ((i & 4) && (j & 32)) continue;
                if ((i & 4) && (j & 128)) continue;
                if ((i & 8) && (j & 64)) continue;
                if ((i & 16) && (j & 64)) continue;
                if ((i & 32) && (j & 128)) continue;
                if ((i & 64) && (j & 16)) continue;
                if ((i & 128) && (j & 32)) continue;
                if (!(i & 16) != !(j & 1)) continue;
                if (!(i & 32) != !(j & 2)) continue;
                if (!(i & 64) != !(j & 4)) continue;
                if (!(i & 128) != !(j & 8)) continue;
                res += dp4[n - 1][j];
            }
            dp4[n][i] = res % MOD;
        }
    }
    v2.push_back(4);
    v3.push_back(8);
    v4.push_back(16);
    for (int n = 2; n < 100; n++) {
        ll res = 0;
        for (int i = 0; i < 16; i++)
            res += dp2[n][i];
        
        v2.push_back(res % MOD);
        res = 0;
        for (int i = 0; i < 64; i++)
            res += dp3[n][i];
        
        v3.push_back(res % MOD);
        res = 0;
        for (int i = 0; i < 256; i++)
            res += dp4[n][i];
        
        v4.push_back(res % MOD);
    }
    bm2 = berlekamp_massey(v2);
    bm3 = berlekamp_massey(v3);
    bm4 = berlekamp_massey(v4);
    
    int T;
    cin >> T;
    while (T--) {
        cin >> M >> N;
        if (M == 2)
            cout << get_nth(bm2, v2, N - 1) << '\n';
        else if (M == 3)
            cout << get_nth(bm3, v3, N - 1) << '\n';
        else if (M == 4)
            cout << get_nth(bm4, v4, N - 1) << '\n';
        else
            cout << ipow(2, N) << '\n';
    }
}
