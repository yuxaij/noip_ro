#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const int MAXN = int(2e6) + 10;
using namespace std;

int n;
int x[MAXN + 10];
int d[MAXN + 10];
int p[MAXN + 10];

bool cmp(const int &a, const int &b) {
    return x[a] < x[b];
}
int main(int argc, char **argv)
{
    int drange_affiner;
    time_t tn = time(NULL);
    srand((unsigned)tn);
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &drange_affiner);

    int max_xrange = int(1e9);
    int max_drange = max_xrange / drange_affiner;

    n = n * (1 - (double) rand() / (~0U>>1) * 0.1);
    for (int j = 1; j <= n; ++j)  {
        x[j] = rand() % (max_xrange - n);
        d[j] = rand() % max_drange;
        p[j] = j;
    }
 
    sort(p + 1, p + n + 1, cmp);

    cout << n << endl;
    for (int i = 1; i <= n; ++i)
        cout << x[p[i]] + i << " " << d[p[i]] << endl;

    while (time(NULL) - tn == 0);
    cerr << "fin case." << endl;
}
