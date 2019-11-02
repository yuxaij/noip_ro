#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int a[100010];
int n, q, maxk, mode;

double randf() {
    return (double) rand() / (~0U>>1);
}
int main(int argc, char **argv) {
    time_t tn = time(NULL);
    srand((unsigned)tn);
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &q);
    sscanf(argv[3], "%d", &maxk);
    sscanf(argv[4], "%d", &mode);

    n = (1 - randf() * 0.05) * n;
    q = (1 - randf() * 0.05) * q;

    for (int i = 1; i <= n; ++i) {
        a[i] = rand() % 2001 - 1000;
    }
    cout << n << " " << q << endl;
    for (int i = 1; i <= n; ++i) {
        cout << a[i];
        if (i == n)
            cout << endl;
        else
            cout << " ";
    }

    if (mode == 0) { // normal
        for (int i = 1; i <= q; ++i) {
            int l = rand() % n + 1;
            int r = rand() % n + 1;
            int k = rand() % maxk + 1;
            if (l > r)
                swap(l, r);
            if (i % 100 == 0) { // IMPOSSIBLE CASE
                if (k != 1)
                    l = max(1, r - rand() % (k-1));
            }
            printf("%d %d %d\n", l, r, k);
        }
    }
    if (mode == 1) { // samelef
        for (int i = 1; i <= q; ++i) {
            int l = 1;
            int r = rand() % n + 1;
            int k = rand() % maxk + 1;
            if (i % 100 == 0) { // IMPOSSIBLE CASE
                if (k != 1)
                    r = rand() % (k-1) + 1;
            }
            cout << l << " " << r << " " << k << endl; 
        }
    }
    if (mode == 2) { // geqhalf
        int minlen = n / 2 + 1;
        int lrange = n - minlen + 1;
        for (int i = 1; i <= q; ++i) {
            int l = rand() % lrange + 1;
            int rstart = l + minlen - 1;
            int r = rand() % (n - rstart + 1) + rstart;
            int k = rand() % maxk + 1;

            cout << l << " " << r << " " << k << endl;
        }
    }
    
    while (time(NULL) - tn == 0);
}
