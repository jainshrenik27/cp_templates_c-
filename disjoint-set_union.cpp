#include <iostream>
#include <vector>
using namespace std;

class Disjoint_set {
    int n;
    vector<int> parent;
    vector<int> sz;

public:
    Disjoint_set(int n) {
        this->n = n;
        parent.resize(n + 1);
        sz.resize(n + 1, 1);

        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x)
            return x;

        return parent[x] = find(parent[x]);   // Path Compression
    }

    void UnionBySize(int u, int v) {
        int pu = find(u);
        int pv = find(v);

        if (pu == pv)
            return;

        if (sz[pu] < sz[pv]) {
            parent[pu] = pv;
            sz[pv] += sz[pu];
        }
        else {
            parent[pv] = pu;
            sz[pu] += sz[pv];
        }
    }

    void printParents() {
        for (int i = 1; i <= n; i++)
            cout << "Parent[" << i << "] = " << find(i) << '\n';
    }
};
