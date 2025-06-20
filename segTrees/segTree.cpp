using namespace std;

struct node {
    int sm;
};

node tree[4 * 200005]; // sum range tree

// fixes the current node at index (x)
void fix_node(int x) {
    tree[x].sm = tree[2 * x].sm + tree[2 * x + 1].sm;
}

// x - current index we are at
// l, r - the current range the current index represents
// p - position to be updated
// v - value to be updated to
void update(int x, int l, int r, int p, int v) {
    // if we are at the leaf - we update the leaf
    if (l == r) {
        tree[x].sm = v;
        return;
    }

    // choose to go to left child or right child
    // update left / right child
    int mid = (l + r) / 2;

    if (p <= mid) update(2 * x, l, mid, p, v);
    else update(2 * x + 1, mid + 1, r, p, v);

    // fix the current node
    fix_node(x);
}


// sum query
// [l, r] is the range of our node
// [ql, qr] is the range we are querying
int query(int x, int l, int r, int ql, int qr) {
    // 1. the range we are querying is not intersecting
    // the current range of the node we are at
    if (ql > r || qr < l) {
        return 0;
    }

    // 2. the node range is enclosed in our query range
    if (ql <= l && r <= qr) {
        return tree[x].sm;
    }

    // 3. it partially intersects
    int mid = (l + r) / 2;
    return query(2 * x, l, mid, ql, qr) +
        query(2 * x + 1, mid + 1, r, ql, qr);
}

int main() {
    // 
}
