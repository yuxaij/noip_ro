#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
const int MAXN = 50;
const int MAXK = 50;
const int MAXM = MAXN + MAXK;
const int mod = (int) 1e9 + 7;
using namespace std;

int fac[MAXM + 10];
int invfac[MAXM + 10];
int f[MAXM + 10][MAXN + 10][MAXK + 10];

int n, m;
int K;

int ex(int a, int p, int b) {
    if (a == 0)
        return 0;
    int t = ex(p % a, a, (-b % a + a) % a);
    return ((long long) p * t + b) / a;
}
void prepare_facs() {
    for (int i = 0; i <= MAXM; ++i)
        fac[i] = i ? (long long) fac[i-1] * i % mod : 1;

    invfac[MAXM] = ex(fac[MAXM], mod, 1);
    for (int i = MAXM; i >= 1; --i)
        invfac[i-1] = (long long) invfac[i] * i % mod;
}
int main() {
    cin >> n >> m;
    cin >> K;

    prepare_facs();

    f[0][0][0] = 1;
    for (int i = 0; i <= m; ++i)
        for (int j = 0; j <= n; ++j)
            for (int k = 0; k <= K; ++k) {
                int u = f[i][j][k];
                if (u == 0)
                    continue;

                for (int di = 0; di <= m - i; ++di) {
                    int dk = max(di - (j+1-(i-k)), 0);
                    (f[i + di][j + 1][k + dk] += (long long) u * invfac[di] % mod) %= mod;
                } 
            }

    cout << (long long) fac[m] * f[m][n][K] % mod << endl;
}
