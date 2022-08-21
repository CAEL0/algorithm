// BOJ 1067 이동

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

const double PI = acos(-1);

void fft(vector<cpx> &arr, cpx w) {
    int n = arr.size() / 2;
    if (n == 0) return;

    vector<cpx> even(n), odd(n);
    for (int i = 0; i < n; i++) {
        even[i] = arr[2 * i];
        odd[i] = arr[2 * i + 1];
    }

    cpx ww = w * w;
    fft(even, ww);
    fft(odd, ww);

    cpx wk(1, 0);
    for (int i = 0; i < n; i++) {
        arr[i] = even[i] + wk * odd[i];
        arr[i + n] = even[i] - wk * odd[i];
        wk *= w;
    }
}
vector<cpx> multiply(vector<cpx> a, vector<cpx> b) {
    int n = 1;
    while (n <= a.size() || n <= b.size())
        n *= 2;
    n *= 2;
    a.resize(n);
    b.resize(n);

    cpx w(cos(2 * PI / n), sin(2 * PI / n));
    fft(a, w);
    fft(b, w);

    vector<cpx> c(n);
    for (int i = 0; i < n; i++)
        c[i] = a[i] * b[i];
    
    fft(c, cpx(1, 0) / w);
    for (int i = 0; i < n; i++)
        c[i] = round(c[i].real() / n);
    return c;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int m;
    cin >> m;

    vector<cpx> x(2 * m), y(m);
    for (int i = 0; i < m; i++) {
        cin >> x[i];
        x[m + i] = x[i];
    }
    for (int i = 0; i < m; i++)
        cin >> y[m - i - 1];
    
    vector<cpx> res = multiply(x, y);
    int ans = 0;
    for (int i = m - 1; i < 2 * m; i++)
        ans = max(ans, (int)res[i].real());
    cout << ans;
}

//--------------------------------------------------------------------------------

void fft(vector<cpx> &arr, bool inv) {
    int n = arr.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (!((j ^= bit) & bit))
            bit >>= 1;
        if (i < j)
            swap(arr[i], arr[j]);
    }
    for (int i = 1; i < n; i <<= 1) {
        double x = inv ? PI / i : -PI / i;
        cpx w(cos(x), sin(x));
        for (int j = 0; j < n; j += i << 1) {
            cpx wk(1, 0);
            for (int k = 0; k < i; k++) {
                cpx tmp = arr[i + j + k] * wk;
                arr[i + j + k] = arr[j + k] - tmp;
                arr[j + k] += tmp;
                wk *= w;
            }
        }
    }
}
void multiply(vector<cpx> &a, vector<cpx> &b) {
    int n = 1;
    while (n <= a.size() || n <= b.size())
        n *= 2;
    n *= 2;
    a.resize(n);
    b.resize(n);
    fft(a, false);
    fft(b, false);

    for (int i = 0; i < n; i++)
        a[i] *= b[i];
    
    fft(a, true);
    for (int i = 0; i < n; i++)
        res[i] = round(a[i].real() / n);
}
