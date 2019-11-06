#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
const int MAXN = 1000;
const int MAXM = 1000;
const int INF = (~0U>>1);
using namespace std;

int maxa[MAXN + 10][MAXN + 10];
int slva[MAXN + 10][MAXN + 10];
int e[MAXN + 10][MAXN + 10];

int main() {
    int n, m, q, a, b, val;

    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            e[i][j] = INF;
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", &a, &b, &val);
        e[a][b] = min(e[a][b], val);
        e[b][a] = min(e[b][a], val);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            maxa[i][j] = i == j ? 0 : e[i][j];
            slva[i][j] = i == j ? 0 : (e[i][j] < INF ? 0 : INF);
        }

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 1; k <= n; ++k) {
                maxa[j][k] = min(maxa[j][k], max(maxa[j][i], maxa[i][k]));

                if (maxa[j][i] > maxa[i][k]) 
                    slva[j][k] = min(slva[j][k], max(slva[j][i], maxa[i][k]));
                else
                    slva[j][k] = min(slva[j][k], max(slva[i][k], maxa[j][i]));
            }

    while (q--) {
        scanf("%d %d", &a, &b);

        if (slva[a][b] == INF)
            cout << -1 << endl;
        else
            cout << slva[a][b] << endl;
    }
}
