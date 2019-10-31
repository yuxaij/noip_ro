#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
const int MAXN = 5000;
using namespace std;

long long A[MAXN + 10];

int f[MAXN + 10][MAXN + 10];
int sufmax[MAXN + 10];

long long sum(int l, int r) {
    return A[r] - A[l-1];
}

int main() {
    int n, a_i;

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a_i;
        A[i] = A[i - 1] + a_i;
    }
    for (int i = 1; i <= n; ++i)
        f[i][1] = 1;

    for (int j = 2; j <= n; ++j) {
        sufmax[j] = 0;
        for (int k = j - 1; k >= 1; --k)
            sufmax[k] = max(sufmax[k + 1], f[j - 1][k]);

        int pt = j;
        for (int i = j; i <= n; ++i) {
            long long sumij = sum(j, i);
            while (pt > 1 && sum(pt - 1, j - 1) <= sumij)
                --pt;

            f[i][j] = sufmax[pt] ? sufmax[pt] + 1 : 0;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        ans = max(ans, f[n][i]);

    cout << n - ans << endl;
}
