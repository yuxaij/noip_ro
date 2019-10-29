#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

int a[5000010];
int cnt = 0;

int main() {
    int x;
    while(scanf("%d", &x) != EOF)
        a[++cnt] = x;

    sort(a + 1, a + cnt + 1);
    int diffs = unique(a + 1, a + cnt + 1) - a - 1;

    cout << diffs << endl;
}
