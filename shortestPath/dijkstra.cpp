#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int N = 100010;

// Has 2 uses:
//  - In adjacency lists, it's an edge from the current vertex to new vertex, in form {distance, new vertex}
//  - In the min-heap, it represents a distance from a vertex v1 to a vertex v2 in the form {dist, v2}
//    Note that we don't know what v1 is, and there can be multiple v2 in the heap (although many will be discarded)
typedef pair<int, int> edge;    // {dist, vertex}

// Adjacency List
vector<edge> edges[N];

// Adding an undirected edge
void add(int u, int v, int d) {
    edges[u].push_back({d, v});
    if (u != v)
        edges[v].push_back({d, u});
}

int dist[N];        // The current shortest distance to a vertex
bool seen[N];       // Whether all paths to veretx have been fully explored
priority_queue<edge, vector<edge>, greater<edge>> pq;   // min-heap of edges

void dijkstra(int s) {
    // Take out the first element
    pq.push({0, s});

    // Continue until there are no more vertices to explore
    // Note that it is possible to create a counter for the number of seen vertices and check
    // to see if ctr==num_vertices, but checking if pq is empty is good practice for modified
    // dijkstra's
    while (!pq.empty()) {
        // Chose the closest vertex
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // All edges around u have already been explored via u
        // Removing this could cause the pq to never empty
        if (seen[u]) continue;

        dist[u] = d;
        seen[u] = true;

        // Edge relaxation
        for (edge v : edges[u]) {
            // I think that's an early exit, as above there exists an if (seen[u]) continue;
            if (seen[v]) continue;

            // Reason why we don't check (dist[u]v.first < dist[v.second]) is because the heap will eventually
            // chose the best one, and repeats will be disregarded using the if (seen[u]) continue;
            pq.push(edge(dist[u] + v.first, v.second));
        }
    }
}

int main() {
    //
}