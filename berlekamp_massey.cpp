#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7;

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
int guess_nth_term(vector<int> x, ll n) {
	if (n < x.sz)
        return x[n];
	
	vector<int> v = berlekamp_massey(x);
	if (v.empty())
        return 0;
	return get_nth(v, x, n);
}
struct elem {
    int x, y, v;
};
vector<int> get_min_poly(int n, vector<elem> M) {
	vector<int> rnd1, rnd2;
	mt19937 rng(0x14004);
	auto randint = [&rng](int lb, int ub) {
		return uniform_int_distribution<int>(lb, ub)(rng);
	};
	for (int i = 0; i < n; i++) {
		rnd1.push_back(randint(1, MOD - 1));
		rnd2.push_back(randint(1, MOD - 1));
	}
	vector<int> gobs;
	for(int i = 0; i < 2 * n + 2; i++) {
		int tmp = 0;
		for(int j = 0; j < n; j++) {
			tmp += (ll)rnd2[j] * rnd1[j] % MOD;
			if (tmp >= MOD)
                tmp -= MOD;
		}
		gobs.push_back(tmp);
		vector<int> nxt(n);
		for (auto &i: M) {
			nxt[i.x] += (ll)i.v * rnd1[i.y] % MOD;
			if (nxt[i.x] >= MOD)
                nxt[i.x] -= MOD;
		}
		rnd1 = nxt;
	}
	auto sol = berlekamp_massey(gobs);
	reverse(sol.begin(), sol.end());
	return sol;
}
ll det(int n, vector<elem> M) {
	vector<int> rnd;
	mt19937 rng(0x14004);
	auto randint = [&rng](int lb, int ub) {
		return uniform_int_distribution<int>(lb, ub)(rng);
	};
	for (int i = 0; i < n; i++)
        rnd.push_back(randint(1, MOD - 1));
	for (auto &i: M)
		i.v = (ll)i.v * rnd[i.y] % MOD;
	
	auto sol = get_min_poly(n, M)[0];
	if (n % 2 == 0)
        sol = MOD - sol;
	for (auto &i: rnd)
        sol = (ll)sol * ipow(i, MOD - 2) % MOD;
	return sol;
}

int mat[101][101];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    for (int i = 0; i < 101; i++)
        mat[i][i] = 1;
    
    int n, k;
    cin >> n >> k;

    int tmp = 0, arr[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> arr[i][j];
            tmp += arr[i][j];
        }
    }
    vector<int> res;
    for (int it = 0; it < 20; it++) {
        int mat_[n][n];
        tmp = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                mat_[i][j] = 0;
                for (int l = 0; l < n; l++) {
                    mat_[i][j] += mat[i][l] * arr[l][j];
                }
                tmp += mat_[i][j];
            }
        }
        res.push_back(tmp);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = mat_[i][j];
    }
    cout << guess_nth_term(res, k - 1);
}
