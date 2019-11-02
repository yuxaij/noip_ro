#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
const int MAXN = int(1e5);
const int MAXD = 17;
const int MAXK = 20;
const int INF = int(1e9);
using namespace std;

int tmpi;
char tmpc;

int n, q;
int maxk;
int a[MAXN + 10];

int f[MAXN + 10][21];
int g[MAXN + 10][21];

int getint() {
    tmpi = 0;
    while (tmpc = getchar(), tmpc < '0' || tmpc > '9');
    while (tmpc >= '0' && tmpc <= '9')
        tmpi = tmpi * 10 + tmpc - '0', tmpc = getchar();
    return tmpi;
}
int main() {

    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    
    while (q--) {
        int l = getint();
        int r = getint();
        int k = getint();

        for (int j = 0; j <= k; ++j)
            g[l-1][j] = f[l-1][j] = -INF;

        g[l-1][1] = 0;
        f[l-1][0] = 0;
        for (int i = l; i <= r; ++i) {
            for (int j = 0; j <= k; ++j) {
                f[i][j] = max(f[i-1][j], g[i-1][j] + a[i]);
                g[i][j] = max(j == 0 ? -INF : f[i][j-1], g[i-1][j] + a[i]);
            }
        }
        if (r - l + 1 < k)
            cout << "IMPOSSIBLE" << endl;
        else
            cout << f[r][k] << endl;
    }
}
