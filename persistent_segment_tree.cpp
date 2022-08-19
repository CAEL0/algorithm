// BOJ 11012 Egg

#include <iostream>
#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second
 
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 100005;
int N, Q, node_idx, roots[MAX];
vector<int> eggs[MAX];

struct Node {
    int v;
    Node *l, *r;
} nodes[200005];

Node* newNode(int v) {
    nodes[++node_idx] = {v, nullptr, nullptr};
    return &nodes[node_idx];
}
Node* addNode(Node* prv, int s, int e, int i, int v) {
    Node* cur = newNode(prv->v + v);
    if (s != e) {
        int m = (s + e) >> 1;
        if (i <= m) {
            cur->l = addNode(prv->l, s, m, i, v);
            cur->r = prv->r;
        } else {
            cur->l = prv->l;
            cur->r = addNode(prv->r, m + 1, e, i, v);
        }
    }
    return cur;
}
int summation(Node* cur, int s, int e, int l, int r) {
    if (r < s || e < l)
        return 0;
    
    if (l <= s && e <= r)
        return cur->v;
    
    int m = (s + e) >> 1;
    return summation(cur->l, s, m, l, r) + summation(cur->r, m + 1, e, l, r);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int T;
    cin >> T;
    while (T--) {
        cin >> N >> Q;
        for (int x = 0; x < MAX; x++)
            eggs[x].clear();
        
        for (int i = 1; i <= N; i++) {
            int x, y;
            cin >> x >> y;
            eggs[x + 1].push_back(y + 1);
        }
        roots[0] = 1;
        node_idx = 0;
        Node* root = newNode(0);
        root->l = root->r = root;
        for (int x = 1; x < MAX; x++) {
            roots[x] = roots[x - 1];
            for (int y: eggs[x]) {
                int tmp = node_idx + 1;
                addNode(&nodes[roots[x]], 1, MAX, y, 1);
                roots[x] = tmp;
            }
        }
        int ans = 0;
        while (Q--) {
            int l, r, b, t;
            cin >> l >> r >> b >> t;
            ans += summation(&nodes[roots[r + 1]], 1, MAX, b + 1, t + 1);
            ans -= summation(&nodes[roots[l]], 1, MAX, b + 1, t + 1);
        }
        cout << ans << '\n';
    }
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

const int MAX = 100005;
int N, Q, node_idx, roots[MAX];
vector<int> eggs[MAX];

struct Node {
    int v, l, r;
} nodes[200005];

int newNode(int v) {
    nodes[++node_idx] = {v, 0, 0};
    return node_idx;
}
int addNode(int prv, int s, int e, int i, int v) {
    int cur = newNode(nodes[prv].v + v);
    if (s != e) {
        int m = (s + e) >> 1;
        if (i <= m) {
            nodes[cur].l = addNode(nodes[prv].l, s, m, i, v);
            nodes[cur].r = nodes[prv].r;
        } else {
            nodes[cur].l = nodes[prv].l;
            nodes[cur].r = addNode(nodes[prv].r, m + 1, e, i, v);
        }
    }
    return cur;
}
int summation(int cur, int s, int e, int l, int r) {
    if (r < s || e < l)
        return 0;
    
    if (l <= s && e <= r)
        return nodes[cur].v;
    
    int m = (s + e) >> 1;
    return summation(nodes[cur].l, s, m, l, r) + summation(nodes[cur].r, m + 1, e, l, r);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    int T;
    cin >> T;
    while (T--) {
        cin >> N >> Q;
        for (int x = 0; x < MAX; x++)
            eggs[x].clear();
        
        for (int i = 1; i <= N; i++) {
            int x, y;
            cin >> x >> y;
            eggs[x + 1].push_back(y + 1);
        }
        node_idx = 0;
        roots[0] = 1;
        newNode(0);
        for (int x = 1; x < MAX; x++) {
            roots[x] = roots[x - 1];
            for (int y: eggs[x]) {
                int tmp = node_idx + 1;
                addNode(roots[x], 1, MAX, y, 1);
                roots[x] = tmp;
            }
        }
        int ans = 0;
        while (Q--) {
            int l, r, b, t;
            cin >> l >> r >> b >> t;
            ans += summation(roots[r + 1], 1, MAX, b + 1, t + 1);
            ans -= summation(roots[l], 1, MAX, b + 1, t + 1);
        }
        cout << ans << '\n';
    }
}
