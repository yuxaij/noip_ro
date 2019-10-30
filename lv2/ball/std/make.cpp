#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const int MAXN = 15;
using namespace std;

int p[MAXN + 10];

int main(int argc, char **argv) {
    int n, m;
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &m);

    time_t tn = time(NULL);
    srand((unsigned)tn);

    for (int i = 1; i <= n; ++i)
        p[i] = i;

    random_shuffle(p + 1, p + n + 1);
    sort(p + 1, p + m + 1);
    cout << n << " " << m << endl;
    for (int i = 1; i <= m; ++i) {
        cout << p[i];
        if (i == m)
            cout << endl;
        else
            cout << " ";
    }

    while (time(NULL) - tn == 0);
    cerr << "fin case." << endl;
}
