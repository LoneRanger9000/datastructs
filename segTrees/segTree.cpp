using namespace std;

typedef struct {
    int sm;
} node;

const int N = 200005;
node tree[2 * N]; // sum range tree

// fixes the current node at index (x)
void fix_node(int x) {
    tree[x].sm = tree[2 * x].sm + tree[2 * x + 1].sm;
}

// Update
// p - position to be updated (1-indexed)
// v - value to be updated to
// x - current index we are at
// [l, r] - the current range the current index represents
void update(int p, int v, int x=1, int l=1, int r=N) {
    // if we are at the leaf - we update the leaf
    if (l == r) {
        tree[x].sm = v;
        return;
    }

    // choose to go to left child or right child
    // update left / right child
    int mid = (l + r) / 2;

    if (p <= mid) update(p, v, 2 * x, l, mid);
    else update(p, v, 2 * x + 1, mid + 1, r);

    // fix the current node
    fix_node(x);
}


// sum query
// [ql, qr] - is the range we are querying (1-indexed)
// x - current index we are at
// [l, r] - is the range of our node
int sumQuery(int ql, int qr, int x=1, int l=1, int r=N) {
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
    return sumQuery(ql, qr, 2 * x, l, mid) +
        sumQuery(ql, qr, 2 * x + 1, mid + 1, r);
}

int main() {
    // 
}
