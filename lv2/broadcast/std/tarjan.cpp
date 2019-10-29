#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
const int MAXN = int(1e5);
const int MAXEDGES = 2 * 2 * 20 * MAXN;

int c[MAXEDGES + 10], nex[MAXEDGES + 10];
int g[MAXN * 2 + 10]; // n leaves + n-1 virtual nodes (n-1 combinations)
int ap = 1;

int entry[MAXN * 2 + 10];
int rank[MAXN * 2 + 10];
int rankid;

int vid;

int q[MAXN * 2 + 10];
int qt;

int n;
int x[MAXN + 10];
int d[MAXN + 10];

void link(int a, int b) {
    c[++ap] = b, nex[ap] = g[a], g[a] = ap;
    c[++ap] = a; // save edge
}

struct vnode {
    int l, r, mid;
    vnode *lef, *rig;

    int id;

    vnode(int l, int r) {
        this->l = l;
        this->r = r;
        this->mid = (l + r) >> 1;

        if (l == r) {
            this->id = l;
            return;
        }
        else this->id = ++vid;
    
        lef = new vnode(l, mid);
        rig = new vnode(mid + 1, r);

        link(this->id, lef->id);
        link(this->id, rig->id);
    }
    void range_link(int l, int r, int x) {
        if (this->l > r || this->r < l)
            return;
        
        if (this->l >= l && this->r <= r) {
            link(x, this->id);
            return;
        }
        lef->range_link(l, r, x);
        rig->range_link(l, r, x);
    }
};
int dfs(int z) {
    int entry_rank = ++rankid;
    rank[z] = entry_rank;
    q[++qt] = z;
    for (int x = g[z]; x; x = nex[x])
        if (entry[c[x]] == 0) { 
            if (rank[c[x]] > 0)
                rank[z] = std::min(rank[z], rank[c[x]]);
            else
                rank[z] = std::min(rank[z], dfs(c[x]));
        } 

    if (rank[z] == entry_rank) {
        int rnid = vid + 1;
        while (rank[q[qt]] >= entry_rank) {
            rnid = std::min(rnid, q[qt]); 
            entry[q[qt--]] = z;
        }
        entry[rnid] = entry[z] = rnid; // entry[entry[a]] to find the leaf leader
    }
    return rank[z];
}
int main() {
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        scanf("%d %d\n", x + i, d + i);

    vid = n;
    vnode *root = new vnode(1, n);

    for (int i = 1; i <= n; ++i) {
        int l, r, j, lef, rig;
        
        l = 1, r = i - 1, lef = i;
        for (; j = (l + r) >> 1, l <= r; )
            if (x[j] < x[i] - d[i])
                l = j + 1;
            else
                lef = j, r = j - 1;

        l = i + 1, r = n, rig = i;
        for (; j = (l + r) >> 1, l <= r; )
            if (x[j] > x[i] + d[i])
                r = j - 1;
            else
                rig = j, l = j + 1;

        root->range_link(lef, rig, i);
    }
    for (int i = 1; i <= n; ++i) // only iterate the n leaves. If a virtual node cannot be visited from a leaf, it does no help.
        if (entry[i] == 0) 
            dfs(i);

    memset(g, 0, sizeof(g));
    memset(nex, 0, sizeof(nex));

    for (int i = 2; i <= ap; i += 2) {
        int a = entry[entry[c[i^1]]], b = entry[entry[c[i]]];
        if (a > 0 && b > 0 && a != b)
            g[b] = true; // reuse g as indeg counter.
    }
    int min_ans = 0;
    int max_ans = 0;
    for (int i = 1; i <= n; ++i)
        if (entry[i] == i) {
            min_ans += g[i] == false; 
            max_ans ++;
        }

    std::cout << min_ans << " " << max_ans << std::endl;
}
