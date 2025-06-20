#include <iostream>
#include <algorithm>

using namespace std;

struct node {
    int sm;
    int mn;
    int mx;
};

// const int N = 1 << 3;
const int N = 1 << 9;
node tree[2 * N][2 * N];

void update(int px, int py, int v, int x, int l, int r);
void updateNested(node nestedTree[], int py, node v, int y, int d, int u);
int sumQuery(int ql, int qr, int qd, int qu, int x, int l, int r);
int nestedSumQuery(node nestedTree[], int qd, int qu, int y, int d, int u);


// DONT CALL
// nestedTree[] - the tree to update
// py - the position to update
// v - what the leaf node will be replaced by
void updateNested(node nestedTree[], int py, node v, int y=1, int d=1, int u=N) {
    // We are at the leaf node, update
    if (d == u) {
        nestedTree[y].sm = v.sm;
        nestedTree[y].mn = v.mn;
        nestedTree[y].mx = v.mx;
        return;
    }

    // choose to go to left child or right child
    int mid = (d + u) / 2;

    if (py <= mid) updateNested(nestedTree, py, v, 2 * y, d, mid);
    else updateNested(nestedTree, py, v, 2 * y + 1, mid + 1, u);

    // fix the current node
    nestedTree[y].sm = nestedTree[2 * y].sm + nestedTree[2 * y + 1].sm;
    nestedTree[y].mn = min(nestedTree[2 * y].mn, nestedTree[2 * y + 1].mn);
    nestedTree[y].mx = max(nestedTree[2 * y].mx, nestedTree[2 * y + 1].mx);
}

// px, py - position (horizontal, vertical)
// v - new value
// x - current x index
// l, r - the range that the current index represents
void update(int px, int py, int v, int x=1, int l=1, int r=N) {
    // If we are at the leaf, then update the leaf
    if (l == r) {
        updateNested(tree[x], py, {v, v, v});
        return;
    }

    // Figure out whether to go left or right
    int mid = (l + r) / 2;

    if (px <= mid) update(px, py, v, 2 * x, l, mid);
    else update(px, py, v, 2 * x + 1, mid + 1, r);

    // fix_node     [Note that the N+py might be wrong]
    int othPos = N + py - 1;
    updateNested(
        tree[x],
        py,
        {
            tree[2 * x][othPos].sm + tree[2 * x + 1][othPos].sm,
            min(tree[2 * x][othPos].mn, tree[2 * x + 1][othPos].mn),
            max(tree[2 * x][othPos].mx, tree[2 * x + 1][othPos].mx)
        }
    );
}

// DONT CALL
// nestedTree[] - the tree to query
// qd, qu - query ranges
// x - current node
// d, u - what ranges the current node represents
int nestedSumQuery(node nestedTree[], int qd, int qu, int y=1, int d=1, int u=N) {
    // cout << "y: " << y << "\n";
    // If there is no overlap
    if (qd > u || qu < d) {
        return 0;
    }

    // Full overlap
    if (qd <= d && u <= qu) {
        // cout << "qd: " << qd << ", u: " << u << ", d: " << d << ", qu: " << qu << "\n";
        // cout << "nestedTree[" << y << "].sm = " << nestedTree[y].sm << "\n";
        return nestedTree[y].sm;
    }

    // Partial overlap
    int mid = (d + u) / 2;
    return nestedSumQuery(nestedTree, qd, qu, 2 * y, d, mid) + 
        nestedSumQuery(nestedTree, qd, qu, 2 * y + 1, mid + 1, u);
}

// ql, qr - left and right bound of square
// qu, qd - top and bottom bound of the square
// x - node of the origional range tree
// l, r - what elements the first nodes is responsible for
int sumQuery(int ql, int qr, int qd, int qu, int x=1, int l=1, int r=N) {
    // cout << "x: " << x << "\n";
    // If there is no overlap
    if (ql > r || qr < l) {
        return 0;
    }

    // Full overlap
    if (ql <= l && r <= qr) {
        // Go into the nested range tree
        return nestedSumQuery(tree[x], qd, qu);
    }

    // Partial overlap
    int mid = (l + r) / 2;
    return sumQuery(ql, qr, qd, qu, 2 * x, l, mid) + 
        sumQuery(ql, qr, qd, qu, 2 * x + 1, mid + 1, r);
}

// DONT CALL
int nestedMinQuery(node nestedTree[], int qd, int qu, int y=1, int d=1, int u=N) {
    // If there is no overlap
    if (qd > u || qu < d) {
        return 2000000000;
    }

    // Full overlap
    if (qd <= d && u <= qu) {
        return nestedTree[y].mn;
    }

    // Partial overlap
    int mid = (d + u) / 2;
    return min(nestedMinQuery(nestedTree, qd, qu, 2 * y, d, mid), 
        nestedMinQuery(nestedTree, qd, qu, 2 * y + 1, mid + 1, u));
}

// ql, qr - left and right bound of square
// qu, qd - top and bottom bound of the square
// x - node of the origional range tree
// l, r - what elements the first nodes is responsible for
int minQuery(int ql, int qr, int qd, int qu, int x=1, int l=1, int r=N) {
    // If there is no overlap
    if (ql > r || qr < l) {
        return 2000000000;
    }

    // Full overlap
    if (ql <= l && r <= qr) {
        // Go into the nested range tree
        return nestedMinQuery(tree[x], qd, qu);
    }

    // Partial overlap
    int mid = (l + r) / 2;
    return min(minQuery(ql, qr, qd, qu, 2 * x, l, mid), 
        minQuery(ql, qr, qd, qu, 2 * x + 1, mid + 1, r));
}

// DONT CALL
int nestedMaxQuery(node nestedTree[], int qd, int qu, int y=1, int d=1, int u=N) {
    // If there is no overlap
    if (qd > u || qu < d) {
        return 0;
    }

    // Full overlap
    if (qd <= d && u <= qu) {
        return nestedTree[y].mx;
    }

    // Partial overlap
    int mid = (d + u) / 2;
    return max(nestedMaxQuery(nestedTree, qd, qu, 2 * y, d, mid), 
        nestedMaxQuery(nestedTree, qd, qu, 2 * y + 1, mid + 1, u));
}

// ql, qr - left and right bound of square
// qu, qd - top and bottom bound of the square
// x - node of the origional range tree
// l, r - what elements the first nodes is responsible for
int maxQuery(int ql, int qr, int qd, int qu, int x=1, int l=1, int r=N) {
    // If there is no overlap
    if (ql > r || qr < l) {
        return 0;
    }

    // Full overlap
    if (ql <= l && r <= qr) {
        // Go into the nested range tree
        return nestedMaxQuery(tree[x], qd, qu);
    }

    // Partial overlap
    int mid = (l + r) / 2;
    return max(maxQuery(ql, qr, qd, qu, 2 * x, l, mid), 
        maxQuery(ql, qr, qd, qu, 2 * x + 1, mid + 1, r));
}

int main() {
    int n = 5;
    int arr[6][6] = {
        {0, 0, 0, 0, 0, 0},
        {0, 1, 2, 3, 4, 5},
        {0, 6, 7, 8, 9, 4},
        {0, 3, 1, 4, 1, 5},
        {0, 2, 7, 1, 8, 2},
        {0, 1, 6, 1, 8, 0}
    };

    cout << "This should show 26: " << sumQuery(1, 2, 2, 4) << "\n";
}

