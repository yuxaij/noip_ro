#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const int MAXN = int(1e5);
using namespace std;

int n, a, b, c, d;
int x[MAXN + 10];
int y[MAXN + 10];

struct point {
    int x, y;
    point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

long long cx(const point &o, const point &b, const point &c) {
    return (long long) (b.x - o.x) * (c.y - o.y) - (long long) (b.y - o.y) * (c.x - o.x);
}
int main() {
    cin >> n;
    cin >> a >> b;
    cin >> c >> d; // sin(alpha), cos(alpha)
    for (int i = 1; i <= n; ++i)
        cin >> x[i] >> y[i];

    point tmp(0, 0);
    point o(0, 0);
    point A(a, b), B(c, d);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j)
            if (x[j] >= x[i] && i != j) {
                tmp.x = x[j] - x[i];
                tmp.y = y[j] - y[i];

                if (cx(o, A, tmp) >= 0 && cx(o, tmp, B) >= 0)
                    ++ans;
                    //cerr << i << " " << j << endl;
            }
    }
    cout << ans << endl;
}
