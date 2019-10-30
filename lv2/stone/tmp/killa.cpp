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

int usa;
int KILLA;

int dfs(int t) {
    
    if (t == n)
        return 1;

    int u = 0;
    
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

        usa += 1<<i;

        if (pt != m || usa + (1<<i) >= KILLA)
            u += dfs(t + 1);

        usa -= 1<<i;

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

    KILLA = 1<<(n+1);

    use[0] = true; // dfs bound

    cout << dfs(0) << endl; 
}
