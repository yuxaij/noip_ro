#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
const int MAXN = int(5e4);
const int MAXD = 16;
const int MAXK = 10;
const int INF = int(1e9);
using namespace std;

int tmpi;
char tmpc;

int n, q;
int maxk;
int A[MAXN + 10], a[MAXN + 10];

int garr[MAXD+1][MAXN + 10][MAXK+1][2];
int farr[MAXD+1][MAXN + 10][MAXK+1][2];

int nbit[1 << MAXD|1];

int getint() {
    tmpi = 0;
    while (tmpc = getchar(), tmpc < '0' || tmpc > '9');
    while (tmpc >= '0' && tmpc <= '9')
        tmpi = tmpi * 10 + tmpc - '0', tmpc = getchar();
    return tmpi;
}
void prepare(int lv, int l, int r) {
    int (*f)[MAXK+1][2] = farr[lv]; 
    int (*g)[MAXK+1][2] = garr[lv];
    int t = (l + r) >> 1;

    int tl = max(l, 1);
    int tr = min(r, n);

    if (l > n || r < 1)
        return;

    if (t >= tl && t <= tr) {  // if not, then the node is not required to be prepared.
        for (int i = t; i >= tl; --i) { 
            for (int j = 0; j <= maxk; ++j)
                for (int c = 0; c <= 1; ++c) {
                    int &u = f[i][j][c];
                    if (j == 0)
                        u = (c == 0) ? 0 : -INF;
                    else
                        u = max(i < t ? f[i+1][j][c] : -INF, g[i][j-1][c] - A[i-1]);

                    if (i == t)
                        g[i][j][c] = j == 0 ? A[i] : -INF;
                    else
                        g[i][j][c] = max(g[i+1][j][c], f[i+1][j][c] + A[i]); 
                }
        }
        for (int i = t + 1; i <= tr; ++i) {
            for (int j = 0; j <= maxk; ++j)
                for (int c = 0; c <= 1; ++c) {
                    int &u = f[i][j][c];
                    if (j == 0)
                        u = (c == 0) ? 0 : -INF;
                    else
                        u = max(i > t+1 ? f[i-1][j][c] : -INF, g[i][j-1][c] + A[i]);

                    if (i == t + 1)
                        g[i][j][c] = j == 0 ? -A[i-1] : -INF;
                    else
                        g[i][j][c] = max(g[i-1][j][c], f[i-1][j][c] - A[i-1]); 
                }
        }
    }

    if (l == r)
        return;

    prepare(lv - 1, l, t);
    prepare(lv - 1, t+1, r);
};
int answer(int l, int r, int k) {
    int depth = nbit[l ^ r];
    int (*f)[MAXK+1][2] = farr[depth];
    if (l == r)
        return f[r][k][0];
    else {
        int ans = -INF;
        for (int i = 0; i <= k; ++i)
            for (int c1 = 0; c1 <= 1; ++c1)
                for (int c2 = 0; c2 <= 1; ++c2)
                    ans = max(ans, f[l][i][c1] + f[r][k - i + (c1 == 1 && c2 == 1)][c2]);
        return ans;
    }
}
int main() {
    for (int i = 1; i <= (1<<MAXD); ++i)
        nbit[i] = nbit[i - 1] + (i == (i & (-i)));  

    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        scanf("%d", a + i);
        A[i] = A[i-1] + a[i];
    }

    maxk = q > 100000 ? 1 : MAXK;
    prepare(MAXD, 0, (1<<MAXD)-1);  

    while (q--) {
        int l = getint();
        int r = getint();
        int k = getint();

        if (r - l + 1 < k)
            printf("IMPOSSIBLE\n");
        else
            printf("%d\n", answer(l, r, k));
    }
}
