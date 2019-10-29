#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define NDEBUG
#include <assert.h>
const int MAXPI = 20;
const int MAXN = int(2e5); 
using namespace std;

int c[2*MAXN + 10], nex[2*MAXN + 10];
int g[MAXN + 10];
int ap = 1;
int n, m, L;

int dfs_pos[MAXN + 10], dfs_pos_out[MAXN + 10];
int dfs_pos_t = 0;
long long nd[2*MAXN + 10];

int depth[MAXN + 10], father[MAXN + 10];
int parent[MAXN + 10][MAXPI];

int vns[MAXN + 10];
int cnt[MAXN + 10];
int qs[MAXN + 10];

int gtit_v;
char gtit_c;

inline int getint() {
    gtit_v = 0;
    while (gtit_c = getchar(), !(gtit_c >= '0' && gtit_c <= '9'));
    while (gtit_c >= '0' && gtit_c <= '9')
        gtit_v = gtit_v * 10 + gtit_c - '0', gtit_c = getchar();
    return gtit_v;
}

bool cmp(const int &a, const int &b) {
    return dfs_pos[a] < dfs_pos[b];
}
void link(int a, int b) {
    c[++ap] = b, nex[ap] = g[a], g[a] = ap;
    c[++ap] = a, nex[ap] = g[b], g[b] = ap;
}
void dfs(int z, int ft) { 
    depth[z] = depth[ft] + 1;
    father[z] = ft;
    parent[z][0] = father[z];
    for (int i = 1; i < MAXPI; ++i)
        parent[z][i] = parent[parent[z][i-1]][i-1];


    dfs_pos[z] = ++dfs_pos_t;
    for (int x = g[z]; x; x = nex[x])
        if (c[x] != ft) {
            ++dfs_pos_t;
            dfs(c[x], z);
        }
    dfs_pos_out[z] = dfs_pos_t;
}
inline bool is_in_sub_tree(int a, int root) {
    return dfs_pos[a] >= dfs_pos[root] && dfs_pos[a] <= dfs_pos_out[root];
}
int get_lca(int x, int y) {
    if (x == 0) return y;
    if (y == 0) return x;
    if (x == y) return x;
    if (depth[x] < depth[y])
        swap(x, y);
    for (int i = MAXPI; i--; )
        if (depth[parent[x][i]] >= depth[y])
            x = parent[x][i];
    if (x == y) return x;
    for (int i = MAXPI; i--; )
        if (parent[x][i] != parent[y][i])
            x = parent[x][i], y = parent[y][i];
    return father[x];
}
void update(int a, int b, int v) {
    for (; a <= dfs_pos_t; a += a & -a)
        nd[a] += v;

    for (++b; b <= dfs_pos_t; b += b & -b)
        nd[b] -= v;
}
long long query(int a) {
    long long ret = 0;
    for (; a; a -= a & -a)
        ret += nd[a];
    return ret;
}
int main() {
    srand((unsigned)time(NULL));
    int a, b, type, p, q, v, k, r, u;

    scanf("%d %d %d", &n, &m, &L);

    for (int i = 1; i < n; ++i) {
        scanf("%d %d", &a, &b);
        link(a, b);
    }

    int root = rand() % n + 1;
    dfs(root, 0); 
    for (int j = 1; j <= m; ++j) {
        scanf("%d", &type);
        if (type == 0) {
            scanf("%d %d %d", &p, &q, &v);

            while (p != q) {
                if (depth[p] < depth[q]) 
                    swap(p, q);

                update(dfs_pos[p], dfs_pos_out[p], v); // node
                update(dfs_pos[p] - 1, dfs_pos_out[p], -v); // edge
                p = father[p];
            }
            update(dfs_pos[p], dfs_pos_out[p], v);
        }
        else {
            scanf("%d", &k);
            int lca = 0;
            int vns_t = 0;
            for (int i = 1; i <= k; ++i) {
                u = getint();
                lca = get_lca(u, lca); 
                vns[++vns_t] = u;
            }
            scanf("%d", &r);
            for (int i = 1; i <= r; ++i) {
                u = getint();
                if (u != lca)
                    vns[++vns_t] = u;
            }
            vns[0] = lca;
            sort(vns + 1, vns + vns_t + 1, cmp);

            int has_lca = (vns[1] == lca);
            int qs_t = 0;
            for (int i = has_lca; i <= vns_t; ++i) {
                while (qs_t > 0 && !is_in_sub_tree(vns[i], qs[qs_t]))
                    qs_t--;
                
                cnt[vns[i]] = 1;
                if (qs_t > 0)
                    cnt[qs[qs_t]]--;
                qs[++qs_t] = vns[i];
            }
            long long ans = -query(dfs_pos[lca] - 1);
            for (int i = has_lca; i <= vns_t; ++i)
                ans += query(dfs_pos[vns[i]]) * cnt[vns[i]];

            cout << ans << endl;
        }
    }

}
