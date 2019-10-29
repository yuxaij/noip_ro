#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const int MAXN = int(1e6);
using namespace std;

int n, K;
int ans;
char s[MAXN + 10];
int fail[MAXN + 10];

int main() {
    while (true) {
        scanf("%d", &n);
        if (n == 0)
            break;
        
        scanf("%d", &K);
        scanf("%s", s + 1);

        ans = 0;
        fail[0] = -1;
        for (int i = 1; i <= n; ++i) {
            int p = fail[i-1];

            while (p >= 0 && s[p+1] != s[i])
                p = fail[p];

            fail[i] = p + 1;

            int clen = i - fail[i];
            int r = i / clen;
            int tlen = i % clen;

            putchar((r / K - r % K >= (tlen != 0)) + 48); // include K = 1
        } 
        cout << endl;
    }
}
