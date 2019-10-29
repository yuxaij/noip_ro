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
long long f[maxN + 10][maxV + 10];
int g[maxN + 10][maxV + 10];

int volume[maxN + 10];
int num[maxN + 10];
int value[maxN + 10];

void dfs_print(int i, int V) {
    if (i == 0)
        return;
    dfs_print(i - 1, g[i][V]);
    cout << (V - g[i][V]) / volume[i];
    
    if (i == n)
        cout << endl;
    else
        cout << " "; 
}
int main() {
    cin >> n >> V;

    memset(g, -1, sizeof(g));
    memset(f, 0, sizeof(f));

    f[0][0] = 0;
    g[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        cin >> num[i] >> volume[i] >> value[i];
        for (int j = 0; j < volume[i]; ++j) {
            int h = 1, t = 0;
            int maxk = V / volume[i];
            int pos = j; 

            for (int k = 0; k <= maxk; ++k) {
                while (h <= t && k - q[h] > num[i])
                    ++h;

                if (g[i-1][pos] != -1) {
                    while (h <= t && (k - q[t]) * value[i] + f[i-1][q[t] * volume[i] + j] <= f[i-1][pos])
                        --t;
                    q[++t] = k;
                }

                if (h <= t) {
                    f[i][pos] = f[i-1][q[h] * volume[i] + j] + (k - q[h]) * value[i];
                    g[i][pos] = q[h] * volume[i] + j;

                }
                else {
                    f[i][pos] = 0;
                    g[i][pos] = -1;
                }

                pos += volume[i]; 
            }
        }
    }
    cout << f[n][V] << endl;
    dfs_print(n, V);
}
