#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MODE_ZERO 0
#define MODE_NORMAL 1
#define INF_MARK (~0U>>1)
const int MAXN = int(5e4);
const int MAXM = 4*MAXN;

int g[MAXN + 10];
int c[2*MAXM + 10], next[2*MAXM + 10], e[2*MAXM + 10], v[2*MAXM + 10];
int ap = 1;

int q[MAXN + 10];
int vis[MAXN + 10], d[MAXN + 10];
int Y;


void link(int a, int b, int low, int high, int cap) {
    int val = rand() % (std::max(high - low, 0) + 1) + std::max(low, 1);
    c[++ap] = b, next[ap] = g[a], g[a] = ap; e[ap] = cap, v[ap] = val;
    c[++ap] = a, next[ap] = g[b], g[b] = ap; e[ap] = 0, v[ap] = val;
}
bool bfs(int s, int t, bool inv=true) {
    int qt = 1;
    vis[s] = Y, d[s] = 0;
    q[qt] = s;
    for (int i = 1; i <= qt; ++i) {
        int z = q[i];
        for (int x = g[z]; x; x = next[x])
            if (e[x^inv] > 0 && vis[c[x]] < Y) {
                vis[c[x]] = Y;
                d[c[x]] = d[z] + (inv ? -1 : 1);
                q[++qt] = c[x];
                
                if (c[x] == t)
                    return true;
            } 
    }
    return false;
}
int dfs(int z, int t, int f) {
    if (z == t)
        return f;
    int nf = 0;
    for (int x = g[z]; x; x = next[x])
        if (e[x] > 0)
            if (vis[c[x]] == Y && d[c[x]] == d[z] + 1) {
                int ef = dfs(c[x], t, f < e[x] ? f : e[x]);
                e[x] -= ef, e[x ^ 1] += ef;
                f -= ef, nf += ef;
            }
    if (nf == 0)
        d[z] = INF_MARK;
    return nf;
}
void matric_graph(int n, int m, int row, int rval, int cval, int cap) {
    for (int i = 0; i < n; ) {
        for (int j = 1; ++i, j <= row; ++j) {
            if (i > n)
                break;
            if (j != 1) {
                link(i - 1, i, 1, cval, rand() % cap + cap), --m; 
                link(i, i - 1, 1, cval, rand() % cap + cap), --m;
            }
            if (i + row <= n)
                link(i, i + row, (long long) (row + 1) * cval / 3, rval, rand() % cap + cap), --m;
        } 
    }
    std::cerr << "graph struct completed." << std::endl;
    while (m--) {
        int a = rand() % n + 1;
        int b = std::min(std::max(1, a - row) + rand() % (2 * row) + 1, n);

        int col_a = (a - 1) / row;
        int col_b = (b - 1) / row;

        if (col_a > col_b)
            std::swap(a, b);

        link(a, b, col_a == col_b ? 1 : std::abs(std::abs(col_a - col_b) - 1) * rval, col_a == col_b ? cval : std::abs(col_a - col_b) * rval, rand() % cap + cap);
    }
}
int main(int argc, char **argv) {
    int n, m, times, mode;

    int seed = (unsigned)time(NULL);
    std::cerr << "random seed " << seed << std::endl;
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &m);
    sscanf(argv[3], "%d", &times);
    sscanf(argv[4], "%d", &mode);

    if (mode == MODE_ZERO)
        times = 0;

    n = (1 - (double) rand() / (~0U>>1) * 0.05) * n;
    m = (1 - (double) rand() / (~0U>>1) * 0.05) * m;

    matric_graph(n, m, rand() % 5 + 5, int(1e8), int(1e6), 20);

    std::cerr << "fin graph." << std::endl;

    int S = 1, T = n;
    int inf = ~0U>>1;
    
    std::cerr << "flow times: " << times << std::endl;
    std::cerr << "find flow:";
    while (++Y, times-- && bfs(T, S, true)) {
        int flow = dfs(S, T, inf);
        std::cerr << " " << flow;
    }
    std::cerr << std::endl;
    bool res = bfs(T, S, true);
    if (res == true)
        std::cerr << "not max flow." << std::endl;

    printf("%d %d\n", n, m);
    printf("%d %d\n", S, T);
    for (int i = 1; i <= m; ++i) {
        int eid = i<<1;
        printf("%d %d %d %d\n", c[eid^1], c[eid], e[eid] + e[eid^1], v[eid]); 
    }
    for (int i = 1; i <= m; ++i) {
        int eid = i<<1;
        printf("%d", e[eid^1]);
        if (i == m)
            printf("\n");
        else
            printf(" ");
    }
}
