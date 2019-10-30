#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
const int maxN = 100;
const int maxV = 200000;
using namespace std;

int rand_rg;
int unit_value;

int n, V;
int q[maxV + 10];
long long f[maxN + 10][maxV + 10];
long long w[maxN + 10][maxV + 10];
int g[maxN + 10][maxV + 10];

int volume[maxN + 10];
int num[maxN + 10];
int value[maxN + 10];

int p[maxV + 10];
int mode;

int main(int argc, char **argv) {
    time_t tn = time(NULL);
    srand((unsigned)tn);
    sscanf(argv[5], "%d", &mode);
    sscanf(argv[1], "%d", &unit_value);    
    sscanf(argv[2], "%d", &V);
    sscanf(argv[3], "%d", &n);
    sscanf(argv[4], "%d", &rand_rg);

    memset(g, -1, sizeof(g));
    memset(f, 0, sizeof(f));

    f[0][0] = 0;
    g[0][0] = 0;
    w[0][0] = 1;

    int fr_l = max(1, (V / n) / 2);

    for (int i = 1; i <= rand_rg; ++i) {
	p[i] = i + fr_l - 1;
        if (ceil(p[i] / 1000) > ceil(V / 1000)) {
            rand_rg = i - 1;
            break;
        }
    }
    if (rand_rg < n) {
        cerr << "error" << endl;
        exit(0);
    }
    random_shuffle(p + 1, p + rand_rg + 1);

    for (int i = 1; i <= n; ++i) {
	volume[i] = p[i];
	num[i] = rand() % min(10 + rand() % 5 + 1, V / volume[i]) + 1;

        if (mode == 1)
            num[i] = 1;
        else if (mode == 2)
            num[i] = V;
        value[i] = unit_value * volume[i] * (1.01 - 0.02 * rand() / (~0U>>1));

        for (int j = 0; j < volume[i]; ++j) {
            int h = 1, t = 0;
            int maxk = V / volume[i];
            int pos = j; 

            for (int k = 0; k <= maxk; ++k) {
                while (h <= t && k - q[h] > num[i])
                    ++h;

                if (g[i-1][pos] != -1) {
                    while (h <= t && (k - q[t]) * value[i] + f[i-1][q[t] * volume[i] + j] < f[i-1][pos])
                        --t;
                    q[++t] = k;
                }

                if (h <= t) {
		    for (int z = h; z <= t; ++z)
                        if (f[i-1][q[z] * volume[i] + j] + (k - q[z]) * value[i] == f[i-1][q[h] * volume[i] + j] + (k - q[h]) * value[i])
			    w[i][pos] += w[i-1][q[z] * volume[i] + j];
			else
			    break;
                    f[i][pos] = f[i-1][q[h] * volume[i] + j] + (k - q[h]) * value[i];
                    g[i][pos] = q[h] * volume[i] + j;
                }
                else {
		    w[i][pos] = 0;
                    f[i][pos] = 0;
                    g[i][pos] = -1;
                }

                pos += volume[i]; 
            }
        }
    }
    int s = -1;
    for (int i = V; i >= 1; --i) 
	if (s == -1 || w[n][i] > w[n][s]) {
            s = i;
            if (w[n][s] > 2)
                break;
        }

    cerr << s << " " << w[n][s] << " " << f[n][s] << endl;

    cout << n << " " << s << endl;
    for (int i = 1; i <= n; ++i)
        cout << num[i] << " " << volume[i] << " " << value[i] << endl;

    while (time(NULL) - tn == 0);
    cerr << "fin case" << endl;
}
