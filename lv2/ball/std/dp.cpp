#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
const int MAXN = 15;
using namespace std;

int f[MAXN + 10][MAXN + 10][MAXN + 10];
int s[3];
int n, m;

int dp(int n, int a, int b, int s2pos) {
    if (s2pos < 0)
        s2pos = 0;

    if (n == 0) // bound
        return 1;

    if (f[n][b][s2pos] != -1)
        return f[n][b][s2pos];
    
    int &u = f[n][b][s2pos];
    u = 0;

    if (n == s[1]) {
        if (s2pos > 0)
            u += dp(n - 1, a - 1, b, 0);
    }
    else {
        if (a > 0 && n != s[2])
            u += dp(n - 1, a - 1, b, s2pos - 1);
        for (int i = 1; i <= b; ++i)
            u += dp(n - 1, a + i - 1, b - i, n == s[2] ? a + i - 1 : s2pos);
    }
    return u;
}
int main() {
    cin >> n >> m;

    if (m != 2)
        exit(0);

    for (int i = 1; i <= 2; ++i)
        cin >> s[i];

    memset(f, -1, sizeof(f));

    cout << dp(n, 0, n, 0) << endl;
}
