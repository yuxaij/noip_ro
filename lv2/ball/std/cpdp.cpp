#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
const int mod = (int) 1e9 + 7;
const int MAXN = 18;
const int MAXK = 18;
const int MAXM = MAXN+MAXK;
using namespace std;

int f[1 << MAXN][MAXK+1];
int n, m;
int K;

int dfs(int t, int k, int S) {
    if (t == m)
        return k == K;
    if (k > K)
        return 0;

    int &u = f[S][k];
    if (u != -1)
        return u;

    u = 0;
    int last = -1;
    for (int i = 0; i < n; ++i) {
        if ((S & (1<<i)) == 0)
            last = i;
        
        u = (u + dfs(t + 1, k + (last == -1), last == -1 ? S : S | (1<<last))) % mod;
    }
    return u; 
}

int main() {
    memset(f, -1, sizeof(f));

    cin >> n >> m;
    cin >> K;

    cout << dfs(0, 0, 0) << endl;
}
