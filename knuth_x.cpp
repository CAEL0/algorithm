// BOJ 19998 스도쿠 (Hard)

#include <bits/stdc++.h>
#define sz size()
#define bk back()
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct Node {
    int row, size;
    Node *column, *left, *right, *up, *down;
};

void make_row(int i, int j, int x, vector<vector<int>> &matrix) {
    vector<int> row(324, 0);

    row[9 * i + j] = 1;
    row[81 + 9 * i + x] = 1;
    row[162 + 9 * j + x] = 1;
    row[243 + 9 * (i / 3 * 3 + j / 3) + x] = 1;

    matrix.push_back(row);
}

vector<Node> make_linked_list(vector<vector<int>> &matrix) {
    int n = matrix.sz;
    int m = matrix[0].sz;
    vector<Node> columns(m + 1);

    for (int j = 0; j <= m; j++) {
        columns[j].size = 0;
        columns[j].left = &columns[(j + m) % (m + 1)];
        columns[j].right = &columns[(j + 1) % (m + 1)];
        columns[j].up = &columns[j];
        columns[j].down = &columns[j];
    }

    for (int i = 0; i < n; i++) {
        Node *prv = nullptr;

        for (int j = 0; j < m; j++) {
            if (!matrix[i][j])
                continue;

            Node *cur = new Node;
            cur->row = i;
            cur->column = &columns[j];
            columns[j].size++;

            cur->up = columns[j].up;
            cur->down = &columns[j];

            columns[j].up->down = cur;
            columns[j].up = cur;

            if (prv) {
                cur->left = prv;
                cur->right = prv->right;

                prv->right->left = cur;
                prv->right = cur;
            } else {
                cur->left = cur;
                cur->right = cur;
            }

            prv = cur;
        }
    }

    return columns;
}

void cover(Node *col) {
    col->left->right = col->right;
    col->right->left = col->left;

    Node *x = col->down;

    while (x != col) {
        Node *y = x->right;

        while (y != x) {
            y->up->down = y->down;
            y->down->up = y->up;
            y->column->size--;

            y = y->right;
        }

        x = x->down;
    }
}

void uncover(Node *col) {
    Node *x = col->up;

    while (x != col) {
        Node *y = x->left;

        while (y != x) {
            y->up->down = y;
            y->down->up = y;
            y->column->size++;

            y = y->left;
        }

        x = x->up;
    }

    col->left->right = col;
    col->right->left = col;
}

bool search(Node *head, vector<int> &ans) {
    if (head->right == head)
        return true;

    int mn = INT_MAX;
    Node *col;
    Node *ptr = head->right;

    while (ptr != head) {
        if (ptr->size == 0)
            return false;

        if (ptr->size < mn) {
            mn = ptr->size;
            col = ptr;
        }

        ptr = ptr->right;
    }

    cover(col);
    Node *x = col->down;

    while (x != col) {
        ans.push_back(x->row);
        Node *y = x->right;

        while (y != x) {
            cover(y->column);
            y = y->right;
        }

        if (search(head, ans))
            return true;

        ans.pop_back();
        y = x->left;

        while (y != x) {
            uncover(y->column);
            y = y->left;
        }

        x = x->down;
    }

    uncover(col);
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<vector<int>> v(9, vector<int>(9));
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            cin >> v[i][j];

    vector<vector<int>> matrix;
    vector<pair<pii, int>> data;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (v[i][j]) {
                make_row(i, j, v[i][j] - 1, matrix);
                data.push_back({{i, j}, v[i][j]});
                continue;
            }

            for (int k = 0; k < 9; k++) {
                make_row(i, j, k, matrix);
                data.push_back({{i, j}, k + 1});
            }
        }
    }

    vector<Node> columns = make_linked_list(matrix);

    vector<int> ans;
    search(&columns.bk, ans);

    for (int x : ans) {
        auto [i, j] = data[x].fi;
        v[i][j] = data[x].se;
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++)
            cout << v[i][j] << ' ';
        cout << '\n';
    }
}
