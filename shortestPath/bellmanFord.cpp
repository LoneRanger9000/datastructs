#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define ll long long
#define MAX 100000000000

const int N = 10010;
const int M = 30010;

int n, m;

typedef pair<ll, ll> edge;
vector<edge> edges[N];
// vector<edge> revEdges[N];

void add(int u, int v, ll d) {
    edges[u].push_back({d, v});
    // revEdges[v].push_back({d, u});
}

ll dp[N][N];

void bellmanFord(int s) {
    // dp[u][j] is the shortest distance from s to u using only j edges

    // Initalizing the DP table
    for (int j = 0; j < n; j++)
        for (int v = 0; v < n; v++)
            dp[j][v] = MAX;
    
    // Base cases
    dp[0][s] = 0;
    dp[1][s] = 0;
    for (edge adj : edges[s])
        dp[1][adj.second] = adj.first;

    // dp[u][j] = min_{v : e(v, u)}(dp[v][j - 1] + e(v, u));
    for (int j = 1; j < n; j++) {
        for (int v = 0; v < n; v++) {
            for (edge nxt : edges[v]) {
                int u = nxt.second;
                int d = nxt.first;
                dp[j][u] = min(dp[j-1][u], dp[j-1][v] + d);
            }
        }
    }
}

int main() {
    // Shortest distance to i from s using only j edges: dp[i][j]

    // dp[u][j] = min_{v : e(v, u)}(dp[v][j - 1] + e(v, u));

    // How is the time complexity O(nm)?
    // So far, there are nm subproblems, and each one takes at worst n time

    // Another way to think for it: for every j, we have to go through every edge once, so by amortization, it is not cubic
    // But shouldn't that mean that (because j is bounded by m) the time complexity is O(m^2)   [Or is j bounded by n]

    // Assuming that there are no minimim cycles, it doesn't make sense to go by a node twice, therefore j should be bounded by n
    // Hence the time complexity is O(nm);


    // NOTE: Becuase of caches and compiler optimizations, it might be worth it to think of whether we should do dp[u][j] or dp[j][u]
}