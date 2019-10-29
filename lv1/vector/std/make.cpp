#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
//#include <utility>
const double pi = acos(-1.);
using namespace std;

set <pair<int, int> > t;

int main(int argc, char **argv) {
    srand((unsigned)time(NULL));
    int n, mode, a, b, c, d;
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &mode);

    cout << n << endl;

    double ang;

    int range1 = (int) 2e3, mid1 = (int) 1e3;
    int range2 = (int) 2e4, mid2 = (int) 1e4;

    if (mode == 0)
        c = 0, d = rand() % mid2 + 1; 
    else
        ang = (double) rand() / (~0U>>1) * pi / 2,
        c = round(cos(ang) * mid2), d = round(sin(ang) * mid2);
    
    ang = (double) rand() / (~0U>>1) * pi / 2,
    a = round(cos(ang) * mid2), b = round(sin(ang) * mid2);
    if ((long long) a * d - (long long) b * c <= 0)
        swap(a, c), swap(b, d);

    cout << a << " " << b << endl;
    cout << c << " " << d << endl;

    t.insert(make_pair(0, 0));
    for (int i = 1; i <= n; ++i) {
        int a = 0, b = 0;
        while (t.find(make_pair(a, b)) != t.end())
            if (rand() & 1)
                a = mid1 - rand() % range1, b = mid1 - rand() % range1; 
            else
                a = mid2 - rand() % range2, b = mid2 - rand() % range2;

        t.insert(make_pair(a, b));
            
        cout << a << " " << b << endl;
    }
}
