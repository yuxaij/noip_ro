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
};
long long *cmp_by_int64::arr = nullptr; // define

std::set <int, cmp_by_int64> q;

int g[MAXN + 10];
int c[2*MAXM + 10], next[2*MAXM + 10], v[2*MAXM + 10], s[2*MAXM + 10];
int ap;

int vis[MAXN + 10];
long long dis[MAXN + 10];
int Y;

int n, m, S, T;

void clear() {
    q.clear();
    cmp_by_int64::arr = dis;
    ap = 1;
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

        vis[S] = ++Y, dis[S] = 0;
        q.insert(S);    
        for (int i = 1; i <= n && !q.empty(); ++i) {
            int nd = *q.begin();
                
            q.erase(q.begin());
            vis[nd] = Y + 1;

            for (int x = g[nd]; x; x = next[x])
                if (s[x] > 0 && vis[c[x]] <= Y)
                    if (vis[c[x]] < Y || dis[nd] + v[x] < dis[c[x]]) {
                        if (vis[c[x]] < Y)
                            vis[c[x]] = Y;
                        else
                            q.erase(c[x]);

                        dis[c[x]] = dis[nd] + v[x];
                        q.insert(c[x]);
                    }            
        }
        if (vis[T] < Y)
            std::cout << "-1" << std::endl;
        else
            std::cout << dis[T] << std::endl;

        Y = Y + 1; // lazy mark.
    }
}
