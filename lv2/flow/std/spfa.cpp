#include <set>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
const int MAXN = int(5e4);
const int MAXM = MAXN * 4;

int g[MAXN + 10];
int c[2*MAXM + 10], next[2*MAXM + 10], v[2*MAXM + 10], s[2*MAXM + 10];
int ap;

int vis[MAXN + 10];
long long dis[MAXN + 10];
int Y;

int in[MAXN + 10], nex[MAXN + 10];

int n, m, S, T;

void clear() {
    memset(g, 0, sizeof(g));
    ap = 1;
}

void link(int a, int b, int cap, int val) {
    c[++ap] = b, next[ap] = g[a], g[a] = ap; v[ap] = val, s[ap] = cap;
    c[++ap] = a, next[ap] = g[b], g[b] = ap; v[ap] = val, s[ap] = 0;
}
int main() {
    int a, b, cap, val; 
    while (true) {
        clear();
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

        vis[S] = ++Y, dis[S] = 0;
        nex[S] = 0;
        in[S] = true;

        for (int ht = S, qt = S; ht; in[ht] = false, ht = nex[ht]) {
            if (ht != qt && dis[nex[ht]] < dis[ht]) { // head swap trick
                int nt = nex[ht];
                nex[ht] = nex[nt];
                nex[nt] = ht;
                ht = nt;
                if (qt == ht)
                    qt = nex[ht];
            }
            for (int x = g[ht]; x; x = next[x])
                if (s[x] > 0)
                    if (vis[c[x]] < Y || dis[ht] + v[x] < dis[c[x]]) {
                        vis[c[x]] = Y, dis[c[x]] = dis[ht] + v[x];
                        if (in[c[x]] == false)
                            if (ht != qt && dis[c[x]] <= dis[nex[ht]]) // push trick
                                nex[c[x]] = nex[ht], nex[ht] = c[x];
                            else
                                nex[qt] = c[x], nex[c[x]] = 0, qt = c[x];
                        in[c[x]] = true;
                    }
        }
        if (vis[T] < Y)
            std::cout << "-1" << std::endl;
        else
            std::cout << dis[T] << std::endl;

        Y = Y + 1; // lazy mark.
    }
}
