#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define c2(i) ((i) * ((i) + 1) / 2)
using namespace std;

long long f[110][2510];
long long mul_tmp[3010];

struct bignum {
    const static int base = 10000;
    int n;
    int d[3010];

    void init(long long v) {
        n = 0;
        memset(d, 0, sizeof(d));
        while (v > 0)
            d[++n] = v % base, v /= base;
        n = max(n, 1);
    }
    bignum(long long v) { this->init(v); }

    void operator *= (const bignum &a) {
        int nn = n + a.n - 1;

        memset(mul_tmp, 0, sizeof(mul_tmp));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= a.n; ++j)
                mul_tmp[i + j - 1] += a.d[j] * d[i];

        for (int i = 1; i <= nn || mul_tmp[i]; ++i) {
            d[i] = mul_tmp[i] % base;
            mul_tmp[i+1] += mul_tmp[i] / base;
            n = i;
        }
    }
    void operator /= (const int &a) {
        int v = 0;
        for (int i = n; i >= 1; --i) {
            v = v * base + d[i];
            d[i] = v / a;
            v = v % a;
        } 
        while (d[n] == 0 && n > 1)
            --n;
    }
    void operator -= (const bignum &a) {
        for (int i = 1; i <= n; ++i) {
            d[i] -= a.d[i];
            if (d[i] < 0)
                d[i] += base, d[i+1]--;
        }
        while (d[n] == 0 && n > 1)
            --n;
    }
    void operator += (const bignum &a) {
        n = max(n, a.n);
        for (int i = 1; i <= n; ++i) {
            d[i] += a.d[i];
            if (d[i] >= base)
                d[i] -= base, d[i+1]++;
        }
        while (d[n+1] > 0)
            ++n;
    }
};
int main() {
    int n, p;
    cin >> n >> p;

    f[0][0] = 1;
    for (int i = 1; i <= n+1; ++i)
        for (int j = c2(i-1); j >= 0; --j)
            for (int k = i - 1; k >= 0; --k) {
                if (j >= c2(i-k-1))
                    f[i][j] -= f[k][j - c2(i-k-1)];
            }
    
    bignum ans(0), base(1), ten(10), temp(0), one(1), cumi(0);

    for (int i = c2(n); i >= 1; --i) {
        cumi += one;
        base *= cumi;
    }
    for (int j = c2(n) - 1; j >= 0; --j) {
        if (f[n+1][j] > 0) {
            temp.init(f[n+1][j]);
            temp *= base;
            temp /= c2(n) - j;

            ans += temp;
        }
    }
    for (int j = c2(n) - 1; j >= 0; --j) {
        if (f[n+1][j] < 0) {
            temp.init(-f[n+1][j]);
            temp *= base;
            temp /= c2(n) - j;

            ans -= temp;
        }
    }

    base.init(base.base);

    for (int i = 1; i <= 51; ++i)
        ans *= base;

    for (int j = c2(n) - 1; j >= 1; --j)
        ans /= j;

    for (int i = ans.n; i >= 2; --i) {
        if (i == 51)            
            cout << ".";
        if (i == ans.n) 
            printf("%d", ans.d[i]);
        else
            printf("%04d", ans.d[i]);
    }
}
