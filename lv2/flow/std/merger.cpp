#include <set>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
const int MAXN = int(5e4);
const int MAXM = int(1e5);

struct cmp_by_int64 {
    static long long *arr; // declare
    bool operator () (const int &a, const int &b) {
        if (arr[a] == arr[b])
            return a < b;
        return arr[a] < arr[b];
    }
} cmper;
long long *cmp_by_int64::arr = nullptr; // define

struct node {
    int id;
    node *lef, *rig, *f;

    void swap_f() {
        if (f->lef == this)
            std::swap(rig, f->rig), f->lef = lef, lef = f;
        else
            std::swap(lef, f->lef), f->rig = rig, rig = f; 
        std::swap(f, f->f);
    }
};
node *merge(node *a, node *b) { // mergable random heap 
    if (a == nullptr)
        std::swap(a, b);
    if (b == nullptr)
        return a;
    if (cmper(a->id, b->id) == false)
        std::swap(a, b);
    a->rig = merge(b, a->rig);
    a->rig->f = a;
    if (rand() & 1)
        std::swap(a->lef, a->rig);
    return a;
}
node *insert(node *root, node *b) {
    return merge(root, b); 
}
node *update(node *root, node *b, bool del=false) {
    if (b != root)
        while (root->f != b)
            b->swap_f();
    root = merge(b->lef, b->rig);
    
    if (del == true)
        b->lef = b->rig = nullptr;
    else
        root = merge(root, b);

    return root;
}
node *erase(node *root, node *b) {
    return update(root, b, true);
}

node nodes[MAXN + 10];

int g[MAXN + 10];
int c[2*MAXM + 10], next[2*MAXM + 10], v[2*MAXM + 10], s[2*MAXM + 10];
int ap;

int vis[MAXN + 10];
long long dis[MAXN + 10];
int Y;

int n, m, S, T;

void clear(int n) {
    cmp_by_int64::arr = dis;
    ap = 1;

    for (int i = 1; i <= n; ++i) {
        node *nt = nodes + i;
        nt->lef = nullptr;
        nt->rig = nullptr;
        nt->f = nullptr;
        nt->id = i;
    }
}

void link(int a, int b, int cap, int val) {
    c[++ap] = b, next[ap] = g[a], g[a] = ap; v[ap] = val, s[ap] = cap;
    c[++ap] = a, next[ap] = g[b], g[b] = ap; v[ap] = val, s[ap] = 0;
}
int main() {
    int a, b, cap, val, n, m; 
    while (true) {
        std::cin >> n >> m;
        if (n == 0 && m == 0)
            break;

        std::cin >> S >> T;
        for (int i = 1; i <= m; ++i) {
            scanf("%d %d %d %d", &a, &b, &cap, &val);
            link(a, b, cap, val);
        }
        for (int i = 1; i <= m; ++i) {
            int eid = i<<1;
            scanf("%d", s + (eid|1));
            s[eid] -= s[eid|1];
        }
        node *root = nullptr;

        vis[S] = ++Y, dis[S] = 0;
        root = insert(root, nodes + S); 
        for (int i = 1; i <= n && root != nullptr; ++i) {
            int nd = root->id;
                
            vis[nd] = Y + 1;
            root = erase(root, root);

            for (int x = g[nd]; x; x = next[x])
                if (s[x] > 0 && vis[c[x]] <= Y)
                    if (vis[c[x]] < Y || dis[nd] + v[x] < dis[c[x]]) {
                        if (vis[c[x]] < Y)
                            vis[c[x]] = Y, root = insert(root, nodes + c[x]);

                        dis[c[x]] = dis[nd] + v[x];
                        root = update(root, nodes + c[x]);
                    }            
        }
        if (vis[T] < Y)
            std::cout << "-1" << std::endl;
        else
            std::cout << dis[T] << std::endl;

        Y = Y + 1; // lazy mark.
    }
}
