// BOJ 11438 LCA 2

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int N, Q;
vector<int> graph[100005];
bool vst[100005];
int depth[100005], sparse[20][100005];

struct Node {
    int idx, d;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N;

    int a, b, c;
    for (int i = 0; i < N - 1; i++) {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    stack<Node> st;
    st.push({1, 2});
    vst[1] = true;
    depth[1] = 1;
    while (st.size()) {
        Node cur = st.top();
        st.pop();
        for (int nxt: graph[cur.idx]) {
            if (!vst[nxt]) {
                vst[nxt] = true;
                depth[nxt] = cur.d;
                sparse[0][nxt] = cur.idx;
                st.push({nxt, cur.d + 1});
            }
        }
    }
    for (int i = 0; i < 19; i++)
        for (int j = 1; j <= N; j++)
            sparse[i + 1][j] = sparse[i][sparse[i][j]];
    
    cin >> Q;

    while (Q--) {
        cin >> a >> b;

        if (depth[a] > depth[b])
            swap(a, b);
        
        int d = depth[b] - depth[a];
        for (int j = 0; j < 20; j++)
            if (d & (1 << j))
                b = sparse[j][b];
        
        if (a == b) {
            cout << a << '\n';
            continue;
        }
        while (1) {
            for (int j = 19; j >= 0; j--) {
                if (sparse[j][a] != sparse[j][b]) {
                    a = sparse[j][a];
                    b = sparse[j][b];
                }
            }
            if (sparse[0][a] == sparse[0][b])
                cout << sparse[0][a] << '\n';
                break;
        }
    }
}
