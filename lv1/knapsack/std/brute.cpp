#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxV = 200000;
const int maxN = 100;
using namespace std;

int n, V;
int q[maxV + 10];
long long farr[2][maxV + 10];

long long *f, *g;

int volume[maxN + 10];
int num[maxN + 10];
int value[maxN + 10];

int main() {
    cin >> n >> V;

    memset(farr, -1, sizeof(farr));

    f = farr[0];
    g = farr[1];
    g[0] = 0;

    for (int i = 1; i <= n; ++i) {
        cin >> num[i] >> volume[i] >> value[i];
        for (int j = 0; j <= V; ++j)
            f[j] = -1;
        for (int j = 0; j < volume[i]; ++j) {
            int h = 1, t = 0;
            int maxk = V / volume[i];
            int pos = j; 

            for (int k = 0; k <= maxk; ++k) {
                while (h <= t && k - q[h] > num[i])
                    ++h;

                if (g[pos] != -1) {
                    while (h <= t && (k - q[t]) * value[i] + g[q[t] * volume[i] + j] <= g[pos])
                        --t;
                    q[++t] = k;
                }

                if (h <= t)
                    f[pos] = g[q[h] * volume[i] + j] + (k - q[h]) * value[i];
                        

                pos += volume[i]; 
            }
        }
        swap(f, g);
    }
    cout << g[V] << endl;
}
