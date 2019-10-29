#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <iomanip>
#define c2(i) ((i) * ((i) + 1) / 2)
using namespace std;

long double f[1<<12];
int n, p;
long double ans = 0;
long double r;

int main() {
    int n;
    cin >> n >> p;

    int S1 = (1<<n)-1;

    f[0] = 1;
    for (int i = 0; i < S1; ++i) {
        int cnt = 0;
        for (int j = 0; j < n; ++j)
            for (int k = j; k < n; ++k) {
                int v = (1<<(k+1))-1-((1<<j)-1);
                if ((v | i) == i)
                    ++cnt;
            }
        r = 1 - (long double) cnt / (n * (n+1) / 2);
        f[i] = f[i] / r;
        for (int j = 0; j < n; ++j)
            for (int k = j; k < n; ++k) {
                int v = (1<<(k+1))-1-((1<<j)-1);
                if ((v | i) != i)
                    f[v | i] += f[i] / (n * (n+1) / 2);
            }
        ans += f[i];
    }
    printf("%.50Lf", ans); 
}
