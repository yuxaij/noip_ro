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
int q[MAXN + 10];

int sbase[MAXN + 10];

long long dfs(int t, int S) {
    if (t == n)
        return 1;
    if (f[S] != -1)
        return f[S];

    long long &u = f[S];
    u = 0;
    
    int saver, pt = 1;
    for (int i = 1; i <= n; ++i) {
        if (use[i] == true)
            continue;
        if (ina[i] && use[a[ina[i] - 1]] == false) // this step guarantee lis >= m. 
            continue;

        while (q[pt] > 0 && q[pt] <= i) 
            ++pt;

        if (pt > m) // illegal
            break;

        saver = q[pt], q[pt] = i;
        use[i] = true;
        u += dfs(t + 1, S - sbase[saver] + 2 * sbase[i]);

        use[i] = false;
        q[pt] = saver;
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
    memset(f, -1, sizeof(f));

    cout << dfs(0, 0) << endl; 
}
