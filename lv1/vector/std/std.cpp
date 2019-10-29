#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const int MAXN = int(1e5);
using namespace std;

long long tmpa, tmpb, a, b, c, d;
long long x[MAXN + 10], y[MAXN + 10];

long long v[MAXN + 10];

int tot[MAXN + 10];
int p[MAXN + 10];
int n;

long long *to_cmp;

bool cmp(const int &a, const int &b) {
    return to_cmp[a] < to_cmp[b];
}
int query(int x) {
    int ret = 0;
    for (; x; x -= x & -x)
        ret += tot[x];
    return ret;
}
void update(int x, int y) {
    for (; x <= n; x += x & -x)
        tot[x] += y;
}
int main() {
    cin >> n;
    cin >> tmpa >> tmpb;
    cin >> c >> d; // sin(alpha), cos(alpha)
    a = tmpa * d - tmpb * c;
    b = tmpb * d + tmpa * c;

    long long f = c * c + d * d;
    for (int i = 1; i <= n; ++i) {
        long long tmpx, tmpy;
        cin >> tmpx >> tmpy;
        x[i] = tmpx * d - tmpy * c;
        y[i] = tmpy * d + tmpx * c;
        p[i] = i;

        v[i] = b * x[i] - a * y[i];
    }

    to_cmp = v;
    sort(p + 1, p + n + 1, cmp);
    reverse(p + 1, p + n + 1);

    long long last = 0;
    int vidx = 0;
    for (int i = 1; i <= n; ++i)
        if (i == 1 || v[p[i]] != last)
            last = v[p[i]], v[p[i]] = ++vidx;
        else
            v[p[i]] = vidx;

    to_cmp = x;
    sort(p + 1, p + n + 1, cmp);

    long long ans = 0;
    for (int i = 1; i <= n; ) {
        int j = i;
        while (j <= n && x[p[j]] == x[p[i]]) {
            ans += query(v[p[j]]) + (j-i);
            ++j;
        }
        while (i < j)
            update(v[p[i]], 1), ++i;
    }
    cout << ans << endl;
}
