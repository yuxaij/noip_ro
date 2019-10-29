#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define assign_run(a, tmp, t, rmp, np, nq) { tmp = a; if (tmp == t && rmp > 0) --rmp; else if (*np == 0) *np = tmp; else *nq = tmp; }
const int MAXPI = 20;
const int MAXN = (int) 5e5;
const int MAXK = (int) 5e5;
using namespace std;

int n, m, k;

int a[MAXK + 10], b[MAXK + 10], v[MAXK + 10];
int rk[MAXK + 10];

int c[2*MAXN + 10], nex[2*MAXN + 10];
int g[MAXN + 10];
int ap = 1;

int depth[MAXN + 10];

int dfs_pos[MAXN + 10], dfs_pos_out[MAXN + 10];
int dfs_pos_t = 0;
int dfs_seq[2*MAXN + 10];

int pilen[2*MAXN + 10];

int bz[2*MAXN + 10][MAXPI];

int p[MAXK + 10][MAXPI];
int q[MAXK + 10][MAXPI];

int gtit_v;
char gtit_c;

int stack_z[MAXN + 10];
int stack_ft[MAXN + 10];
int stack_x[MAXN + 10];
int s_t = 0;

inline int getint() {
    gtit_v = 0;
    while (gtit_c = getchar(), !(gtit_c >= '0' && gtit_c <= '9'));
    while (gtit_c >= '0' && gtit_c <= '9')
        gtit_v = gtit_v * 10 + gtit_c - '0', gtit_c = getchar();
    return gtit_v;
}

bool cmp(const int &a, const int &b) {
    return v[a] < v[b];
}
void link(int a, int b) {
    c[++ap] = b, nex[ap] = g[a], g[a] = ap;
    c[++ap] = a, nex[ap] = g[b], g[b] = ap;
}
void dfs_by_stack(int root) {
    s_t = 1;
    stack_z[1] = root;
    stack_ft[1] = 0;
    stack_x[1] = 0;

    int cnt = 0;
    while (s_t != 0) {
        int &z = stack_z[s_t], &ft = stack_ft[s_t], &x = stack_x[s_t];
        if (x == 0) {
            x = g[z];
            depth[z] = depth[ft] + 1;
            ++cnt;
            dfs_pos[z] = ++dfs_pos_t;
            dfs_seq[dfs_pos[z]] = z;
        }
        else
            x = nex[x];
        if (x == 0) {
            dfs_pos_out[z] = dfs_pos_t;
            --s_t;
            continue;
        }
        else if (c[x] != ft) {
            stack_z[++s_t] = c[x];
            stack_ft[s_t] = z;
            stack_x[s_t] = 0;
            dfs_seq[++dfs_pos_t] = z;
        }
    }
    //cerr << "total nodes:" << n << endl;
    //cerr << "visited nodes: " << cnt << endl;
}
inline int bz_merge(int a, int b) {
    return depth[a] < depth[b] ? a : b;
}
void build_bz() {
    for (int i = dfs_pos_t; i >= 1; --i) {
        bz[i][0] = dfs_seq[i];

        for (int j = 1; j < MAXPI; ++j) {
            if (i + (1<<j) - 1 > dfs_pos_t)
                break;
            bz[i][j] = bz_merge(bz[i][j-1], bz[i+(1<<(j-1))][j-1]);
        }
    }
    int r = 0;
    for (int i = 1; i <= dfs_pos_t; ++i) {
        if ((1<<r)*2 < i)
            r++;

        pilen[i] = r;
    }
}
inline int lca(int a, int b) {
    if (dfs_pos[a] > dfs_pos[b])
        swap(a, b);
    int len = dfs_pos[b] - dfs_pos[a] + 1; 
    return bz_merge(bz[dfs_pos[a]][pilen[len]], bz[dfs_pos[b] - (1<<pilen[len]) + 1][pilen[len]]);
}
void get_path_intersection(int p, int q, int u, int v, int *np, int *nq) {
    int s = lca(p, q), w = lca(u, v);
    int t = lca(s, w);
    int rmp = 2;
    int tmp;

    assign_run(lca(p, u), tmp, t, rmp, np, nq);
    assign_run(lca(p, v), tmp, t, rmp, np, nq);
    assign_run(lca(q, u), tmp, t, rmp, np, nq);
    assign_run(lca(q, v), tmp, t, rmp, np, nq);

    if (*np == *nq && (depth[*np] < depth[s] || depth[*np] < depth[w]))
        *np = *nq = 0;
}
bool node_in_path(int z, int a, int b) {
    return a && b && depth[z] >= depth[lca(a, b)] && (dfs_pos[z] <= dfs_pos[a] && dfs_pos_out[z] >= dfs_pos[a] || dfs_pos[z] <= dfs_pos[b] && dfs_pos_out[z] >= dfs_pos[b]);
}
int main() {
    srand((unsigned)time(NULL));
    int x, y, u, type;

    scanf("%d %d %d", &n, &k, &m);
    for (int i = 1; i < n; ++i) {
        x = getint(), y = getint();
        link(x, y);
    }

    int root = rand() % n + 1;
    dfs_by_stack(root);
    //cerr << "finish dfs with root: " << root << endl;

    build_bz();

    for (int i = 1; i <= k; ++i) {
        a[i] = getint(), b[i] = getint(), v[i] = getint();
        rk[i] = i;
    }
    sort(rk + 1, rk + k + 1, cmp);

    for (int i = k; i >= 1; --i) {
        p[i][0] = a[rk[i]];
        q[i][0] = b[rk[i]];
        for (int j = 1; j < MAXPI; ++j) {
            if (i + (1<<j) - 1 > k)
                break;

            int ni = i + (1<<(j-1));
            get_path_intersection(p[i][j-1], q[i][j-1], p[ni][j-1], q[ni][j-1], p[i] + j, q[i] + j);
        }
    }

    int s = 1;

    rk[k + 1] = 0, v[0] = -1;
    for (int i = 1; i <= m; ++i) {
        type = getint();
        if (type == 0)
            s++;
        else {
            u = getint();
            int cur = s;
            for (int j = MAXPI; j--; )
                if (node_in_path(u, p[cur][j], q[cur][j]))
                    cur += 1<<j;
        
            cout << v[rk[cur]] << endl;
        }
    }
}
