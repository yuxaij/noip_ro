#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include "drawer.cpp"
const int MAXN = int(3e6);
using namespace std;

int p[MAXN + 10];
int savep[MAXN + 10];
int a[MAXN + 10];
int v[MAXN + 10];

int pn_parts = 5;
int ppart_sizes[5] = {40, 30, 15, 8, 7};
double ppart_powes[5] = {0, 0.5, 0.7, 0.9, 0.8};

int main(int argc, char **argv) {
    time_t tn = time(NULL);
    srand((unsigned)tn);

    int n, m, expa, maxa;
    double lowrates;

    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &m);
    sscanf(argv[3], "%d", &expa);
    sscanf(argv[4], "%d", &maxa);

    drawer->draw(m, n, 1, MAXN, p, pn_parts, ppart_sizes, ppart_powes);
    cerr << "fin draw." << endl;

    sort(p + 1, p + m + 1);
    int vp = 1;
    for (int i = 1; i <= m; ++i)
        savep[i] = p[i];
    for (int i = 2; i <= m; ++i) {
        while (vp < i && savep[i] - savep[vp] > 1)
            ++vp;

        swap(p[i], p[vp + rand() % (i - vp + 1)]);
    }

    int pos = n;

    long long last = 0;
    for (int i = m; i >= 1; --i) {
        long long totmax = (long long) p[i] * expa;

        if (i != m)
            totmax = min(totmax, last);

        int saveexpa = expa;
        int savemaxa = maxa;
        expa = ceil((double) totmax / p[i]);
        maxa = ceil((double) savemaxa / saveexpa * expa);

        long long offset = max((long long) (totmax * (1 - 1. / m)), 1LL);
        long long tot = offset + (((long long) rand() << 32) | rand()) % (totmax - offset + 1);

        last = tot;

        for (int j = p[i]; j >= 1; --j) {
            long long minb = max(0LL, tot - (j - 1LL) * expa);
            long long maxb = min((long long) maxa, tot);
            long long expb = min((long long) maxb, max(0LL, (long long) (tot - (j - 1LL) * expa * 0.95)));

            if (minb > expb || minb > maxb || expb > maxb) {
                cerr << "err " << minb << " " << expb << " " << maxb << endl;
                exit(0);
            }

            double prob = min(0.5, (expb - minb + 1.) / (maxb - expb + 1.));

            long long low, high;

            if (((double) rand() / (~0U>>1)) < prob)
                low = expb, high = maxb;
            else
                low = minb, high = expb;
 
            v[j] = (((long long) rand() << 32) | rand()) % (high - low + 1) + low;
            tot -= v[j];
        }
        random_shuffle(v + 1, v + p[i] + 1);
        for (int j = 1; j <= p[i]; ++j)
            a[pos--] = v[j];

        expa = saveexpa;
        maxa = savemaxa;
    }
    if (pos != 0) {
        cerr << "err pos " << pos << endl;
        exit(0);
    }
    cout << n << endl;
    for (int i = 1; i <= n; ++i) {
        printf("%d", a[i]);
        if (i == n)
            putchar('\n');
        else
            putchar(' ');
    }
}
