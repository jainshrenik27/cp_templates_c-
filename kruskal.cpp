class DisjointSet {
public:
    vector<int> parent, sz;

    DisjointSet(int n) {
        parent.resize(n);
        sz.resize(n, 1);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);
    }

    void UnionBySize(int u, int v) {
        u = find(u);
        v = find(v);

        if (u == v) return;

        if (sz[u] < sz[v]) {
            parent[u] = v;
            sz[v] += sz[u];
        } else {
            parent[v] = u;
            sz[u] += sz[v];
        }
    }
};

class Solution {
public:
    pair<int, vector<vector<int>>> kruskalMST(int V, vector<vector<int>> adj[]) {

        vector<vector<int>> edges;

        // Create edge list
        for (int u = 0; u < V; u++) {
            for (auto &it : adj[u]) {
                int v = it[0];
                int wt = it[1];

                if (u < v)          // avoid duplicate edges
                    edges.push_back({wt, u, v});
            }
        }

        sort(edges.begin(), edges.end());

        DisjointSet ds(V);

        int mstWeight = 0;
        vector<vector<int>> mstEdges;

        for (auto &edge : edges) {

            int wt = edge[0];
            int u  = edge[1];
            int v  = edge[2];

            if (ds.find(u) != ds.find(v)) {

                ds.UnionBySize(u, v);

                mstWeight += wt;

                mstEdges.push_back({u, v, wt});

                // MST completed
                if (mstEdges.size() == V - 1)
                    break;
            }
        }

        return {mstWeight, mstEdges};
    }
};
