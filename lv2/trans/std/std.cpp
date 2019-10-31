#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
const int MAXN = 300;
const int MAXK = 300;
const int MAXM = MAXN + MAXK;
const int mod = (int) 1e9 + 7;
using namespace std;

int arrf[MAXN + 10][MAXK + 10];
int arrg[MAXM + 10][MAXN + 10][2];
int arrG[MAXM + 10][MAXN + 10][2];

int fac[MAXM + 10];
int invfac[MAXM + 10];

int n, m;
int K;

int ex(int a, int p, int b) {
    if (a == 0)
        return 0;
    int t = ex(p % a, a, (-b % a + a) % a);
    return ((long long) p * t + b) / a;
}
int c(int n, int m) {
    if (m > n) { // never take that.
        cerr << "error" << endl;
        exit(0);
    }
    return (long long) fac[n] * invfac[m] % mod * invfac[n-m] % mod;
}
void prepare_facs() {
    for (int i = 0; i <= MAXM; ++i)
        fac[i] = i ? (long long) fac[i-1] * i % mod : 1;

    invfac[MAXM] = ex(fac[MAXM], mod, 1);
    for (int i = MAXM; i >= 1; --i)
        invfac[i-1] = (long long) invfac[i] * i % mod;
}

int f(int n, int k) {
    if (n == 0) // bound
        return k == 0;
    int &u = arrf[n][k];

    if (u != -1)
        return u;

    u = k ? (long long) n * f(n, k-1) % mod : 0;
    for (int i = 1; i <= n; ++i)
        u = (u + (long long) f(i-1, k) * f(n-i, 0) % mod * c(n-1+k, n-i) % mod * (n - i + 1)) % mod;
    return u;
}
int G(int n, int m, int k);
int g(int i, int j, int k) {
    if (i <= 0) // bound
        return i == 0 && j == 0 && k == 0;

    int &u = arrg[i][j][k == K];

    if (u != -1)
        return u;

    if (i == j)
        u = f(i, k);
    else {
        u = 0;
        for (int lq = 1; lq <= i; ++lq)
            if (lq <= j)
                u = (u + (long long) f(lq, 0) * G(i-lq, j-lq, k) % mod * c(i+k, lq)) % mod;
    }
    return u;
}
int G(int i, int j, int k) {
    if (i < 0 || j < 0) // undefines check.
        return 0;

    int &u = arrG[i][j][k == K];
    if (u != -1)
        return u;

    u = j ? (G(i, j-1, k) + g(i, j-1, k)) % mod : 0;
    return u;
}
int main() {
    cin >> n >> m;
    cin >> K;

    memset(arrf, -1, sizeof(arrf));
    memset(arrg, -1, sizeof(arrg));
    memset(arrG, -1, sizeof(arrG));

    prepare_facs();

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = (ans + g(m - K, i, K)) % mod;
    }

    cout << ans << endl;
}
