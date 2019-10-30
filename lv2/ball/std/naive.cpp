#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
const int MAXN = 15;
const int MAXS = pow(3, MAXN);
using namespace std;

int n, m;
int a[MAXN + 10], ina[MAXN + 10];

long long f[MAXS + 10];

bool use[MAXN + 10];
int pos[MAXN + 10];
int dp[MAXN + 10];

int sbase[MAXN + 10];

long long dfs(int t, int S) {
    if (t == n)
        return 1;

    long long u = 0;
    
    int saver, pt = 0;
    for (int i = 1; i <= n; ++i) {
        if (use[i] == true)
            continue;
        if (ina[i] && use[a[ina[i] - 1]] == false) // this step guarantee lis >= m. 
            continue;

        pt = 1;
        for (int j = 0; j < t; ++j)
            if (pos[j] < i && dp[pos[j]] + 1 > pt)
                pt = dp[pos[j]] + 1;

        if (pt > m) // illegal
            break;

        pos[t] = i;
        dp[i] = pt;
        use[i] = true;
        u += dfs(t + 1, 0);

        use[i] = false;
    }
    return u;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> a[i];
        ina[a[i]] = i;
    }
    for (int i = 1; i <= n; ++i)
        sbase[i] = i == 1 ? 1 : sbase[i-1] * 3; 

    use[0] = true; // dfs bound

    cout << dfs(0, 0) << endl; 
}
