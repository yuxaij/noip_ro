#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
const int MAXN = 1000;
const int MAXM = 1000;
const int INF = (~0U>>1);
using namespace std;

int g[MAXN + 10];
int c[2*MAXM + 10], nex[2*MAXM + 10], v[2*MAXM + 10];
int ap = 1;

int maxa[MAXN + 10], slva[MAXN + 10];
int vis[MAXN + 10];

void link(int a, int b, int val) {
    c[++ap] = b, nex[ap] = g[a], g[a] = ap; v[ap] = val;
    c[++ap] = a, nex[ap] = g[b], g[b] = ap; v[ap] = val;
}

int main() {
    int n, m, q, a, b, val;

    cin >> n >> m >> q;
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &a, &b, &val);
        link(a, b, val);
    }
    while (q--) {
        scanf("%d %d", &a, &b);
        for (int i = 0; i <= n; ++i) {
            maxa[i] = slva[i] = INF;
            vis[i] = 0;
        }

        maxa[a] = 0;
        slva[a] = 0;
        for (int i = 1; i <= n; ++i) {
            int nt = 0;
            for (int j = 1; j <= n; ++j)
                if (vis[j] == 1 && slva[j] < slva[nt])
                    nt = j;
            if (slva[nt] == INF)
                break;

            vis[nt] = 2;
            for (int x = g[nt]; x; x = nex[x]) {
                if (maxa[c[x]] > maxa[nt] && maxa[c[x]] > v[x])
                    maxa[c[x]] = max(maxa[nt], v[x]);
                if (v[x] < maxa[nt])
                    slva[c[x]] = min(slva[c[x]], max(v[x], slva[nt]));
                else
                    slva[c[x]] = min(slva[c[x]], maxa[nt]);
            }
        }
        if (slva[b] == INF)
            cout << -1 << endl;
        else
            cout << slva[b] << endl;
    }
}
