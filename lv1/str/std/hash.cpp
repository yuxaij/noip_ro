#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const int mod = (int) 1e9 + 7;
const int MAXN = (int) 1e6;
const long long hbase = 173;
using namespace std;

int hv[MAXN + 10];
int hpow[MAXN + 10];
char s[MAXN + 10];

int mark[MAXN + 10];

int n, K;

inline int get_hash(const int &l, const int &r) {
    return (hv[r] - (long long) hv[l-1] * hpow[r - (l-1)] % mod + mod) % mod;
}

int main() {
    hpow[0] = 1;
    for (int i = 1; i <= MAXN; ++i)
        hpow[i] = hpow[i-1] * hbase % mod;
    while (true) {
        scanf("%d", &n);
        if (n == 0)
            break;
        
        scanf("%d", &K);
        scanf("%s", s + 1);

        hv[0] = 0; 
        for (int i = 1; i <= n; ++i) {
            hv[i] = (hv[i-1] * hbase + s[i] - 'a') % mod;
            mark[i] = 0;
        }

        for (int i = 1; i <= n; ++i) {
            if (i * K > n)
                break;
            if (get_hash(1, i * (K-1)) == get_hash(i+1, i * K)) {
                int bias = i * K;
                int l = 1, r = i, j;
                int an = 0;
                for (; j = (l + r) >> 1, l <= r; )
                    if (bias + j <= n && get_hash(1, j) == get_hash(bias + 1, bias + j))
                        an = j, l = j + 1;
                    else
                        r = j - 1;

                mark[bias]++, mark[bias + an + 1]--;
            }
        }
        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            cnt += mark[i];
            putchar((cnt > 0) + 48);
        }
        cout << endl;
    }
}
