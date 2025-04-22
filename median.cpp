// BOJ 1665 가운데를 말해요

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Median {
    priority_queue<ll> left;
    priority_queue<ll, vector<ll>, greater<ll>> right;

    ll get_median() { return left.top(); }

    void add(ll x) {
        if (left.empty()) {
            left.push(x);
            return;
        }

        ll median = get_median();
        if (x <= median) {
            if (left.sz > right.sz) {
                left.pop();
                right.push(median);
            }

            left.push(x);
        } else {
            right.push(x);

            if (left.sz < right.sz) {
                left.push(right.top());
                right.pop();
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    Median m;
    while (n--) {
        int x;
        cin >> x;

        m.add(x);

        cout << m.get_median() << '\n';
    }
}

//--------------------------------------------------------------------------------

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Median {
    map<ll, ll> left, right;
    ll left_sum = 0;
    ll right_sum = 0;
    ll left_cnt = 0;
    ll right_cnt = 0;

    ll get_median() { return left.rbegin()->fi; }

    void add(ll x) {
        if (left_cnt == 0) {
            add_left(x);
            return;
        }

        ll median = get_median();
        if (x <= median) {
            if (left_cnt == right_cnt + 1) {
                erase_left(median);
                add_right(median);
            }

            add_left(x);
        } else {
            add_right(x);

            if (left_cnt + 1 == right_cnt) {
                ll mn = right.begin()->fi;
                erase_right(mn);
                add_left(mn);
            }
        }
    }

    void erase(ll x) {
        ll median = get_median();
        if (x <= median) {
            if (left_cnt == right_cnt) {
                ll mn = right.begin()->fi;
                erase_right(mn);
                add_left(mn);
            }

            erase_left(x);
        } else {
            if (left_cnt == right_cnt + 1) {
                erase_left(median);
                add_right(median);
            }

            erase_right(x);
        }
    }

    void add_left(ll x) {
        left[x]++;
        left_sum += x;
        left_cnt++;
    }

    void add_right(ll x) {
        right[x]++;
        right_sum += x;
        right_cnt++;
    }

    void erase_left(ll x) {
        if (--left[x] == 0)
            left.erase(x);
        left_sum -= x;
        left_cnt--;
    }

    void erase_right(ll x) {
        if (--right[x] == 0)
            right.erase(x);
        right_sum -= x;
        right_cnt--;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    Median m;
    while (n--) {
        int x;
        cin >> x;

        m.add(x);

        cout << m.get_median() << '\n';
    }
}
