#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
const int MAXN = int(3e6);
using namespace std;

int tmpi;
char tmpc;

long long A[MAXN + 10], h[MAXN + 10];
int f[MAXN + 10];

int s[MAXN + 10];

int n;

int getint() {
    tmpi = 0;
    while (tmpc = getchar(), tmpc < '0' || tmpc > '9');
    while (tmpc >= '0' && tmpc <= '9')
        tmpi = tmpi * 10 + tmpc - '0', tmpc = getchar();
    return tmpi;
}
int main() {
    cin >> n;

    int sj = 0, st = 0;
    
    f[0] = 0, h[0] = 0;
    s[st] = 0;
    for (int i = 1; i <= n; ++i) {
        int a_i = getint();
        A[i] = A[i - 1] + a_i;

        while (sj < st && h[s[sj+1]] <= A[i])
            ++sj;

        f[i] = f[s[sj]] + 1;

        h[i] = 2 * A[i] - A[s[sj]];

        while (sj < st && h[s[st]] >= h[i])
            --st;
        
        s[++st] = i;
    }
    cout << n - f[n] << endl;
}
