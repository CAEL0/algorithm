// BOJ 10446 Algorist Club

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct EdgeColoring {
    int n;
    vector<pii> edges;
    vector<int> free_color;
    vector<vector<int>> color;
    vector<vector<int>> neighbor;

    EdgeColoring(int n, vector<pii> &edges) : n(n), edges(edges) {
        free_color.resize(n + 1, 1);
        color.resize(n + 1, vector<int>(n + 1));
        neighbor.resize(n + 1, vector<int>(n + 2));
    }

    void solve() {
        int idx = 0;
        while (idx < edges.sz) {
            int x = edges[idx].fi;
            int y = edges[idx].se;
            idx++;

            int c = free_color[x];
            vector<pii> fan = {make_pair(y, free_color[y])};
            vector<bool> vst(n + 2);
            while (1) {
                int z = fan.bk.fi;
                int d = fan.bk.se;

                if (!neighbor[z][c]) {
                    while (fan.sz) {
                        c = coloring(x, fan.bk.fi, c);
                        fan.pop_back();
                    }
                    break;
                }

                if (!neighbor[x][d]) {
                    while (fan.sz) {
                        coloring(x, fan.bk.fi, fan.bk.se);
                        fan.pop_back();
                    }
                    break;
                }

                if (vst[d])
                    break;

                vst[d] = true;
                fan.push_back(make_pair(neighbor[x][d], free_color[neighbor[x][d]]));
            }

            if (color[x][y])
                continue;

            int cc = c;
            int z = fan.bk.fi;
            int d = fan.bk.se;
            while (z) {
                z = flip(z, cc, d);
                swap(cc, d);
            }

            if (!neighbor[x][c]) {
                idx--;
                continue;
            }

            fan.pop_back();
            while (fan.sz && fan.bk.se != cc)
                fan.pop_back();

            while (fan.sz) {
                coloring(x, fan.bk.fi, fan.bk.se);
                fan.pop_back();
            }
        }
    }

    int coloring(int x, int y, int c) {
        int d = color[x][y];
        color[x][y] = c;
        color[y][x] = c;
        neighbor[x][c] = y;
        neighbor[y][c] = x;
        neighbor[x][d] = 0;
        neighbor[y][d] = 0;

        if (d) {
            free_color[x] = d;
            free_color[y] = d;
        } else {
            update(x);
            update(y);
        }

        return d;
    }

    void update(int x) {
        int c = 1;
        while (neighbor[x][c])
            c++;

        free_color[x] = c;
    }

    int flip(int x, int c, int d) {
        int y = neighbor[x][c];
        swap(neighbor[x][c], neighbor[x][d]);

        if (y) {
            color[x][y] = d;
            color[y][x] = d;
        }

        if (!neighbor[x][c])
            free_color[x] = c;

        if (!neighbor[x][d])
            free_color[x] = d;

        return y;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<pii> edges(m);
        for (int i = 0; i < m; i++)
            cin >> edges[i].fi >> edges[i].se;

        EdgeColoring ec(n, edges);
        ec.solve();

        for (pii p : edges)
            cout << p.fi << ' ' << p.se << ' ' << ec.color[p.fi][p.se] << '\n';
    }
}
