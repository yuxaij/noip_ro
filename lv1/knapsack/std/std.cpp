#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const int MAXN = 100;
const int MAXV = 200000;
using namespace std;

int n, V;
int num[MAXN + 10], volume[MAXN + 10], value[MAXN + 10];

long long f_arr[MAXV + 10];
long long g_arr[MAXV + 10];
long long *f = f_arr;
long long *g = g_arr;

int fr_arr[MAXV + 10], nfr_arr[MAXV + 10];
int *fr = fr_arr;
int *nfr = nfr_arr;

int q[MAXV + 10];

int vis[MAXV + 10];
int Y;

long long ans = 0;
int ans_r[MAXN + 10];

void dp(int l, int r, int s, int t) {
    if (r - l == 1)
        return;

    int mid = (l + r + 1) >> 1; // r - l = 1, choose r, correctness trick (not used in this prob)

    f[s] = 0, fr[s] = -1, vis[s] = ++Y;
    for (int i = l+1; i <= r; ++i) {
        for (int j = 0; j < volume[i]; ++j) {
            if (s + j > t) 
                break;
            int maxk = (t - (s + j)) / volume[i]; 
            int ht = 1, qt = 0;
            int pos = s + j;
            for (int k = 0; k <= maxk; ++k) {
                while (ht <= qt && k - q[ht] > num[i])
                    ++ht;

                if (vis[pos] == Y) {
                    while (ht <= qt && f[q[qt] * volume[i] + j + s] + value[i] * (k - q[qt]) <= f[pos])
                        --qt;

                    q[++qt] = k;
                }

                if (ht <= qt) {
                    g[pos] = f[q[ht] * volume[i] + j + s] + value[i] * (k - q[ht]);

                    if (i == mid) nfr[pos] = pos;
                    else nfr[pos] = fr[q[ht] * volume[i] + j + s];

                    vis[pos] = Y;
                }
                else 
                    g[pos] = 0, nfr[pos] = -1;

                pos += volume[i];
            }
        }
        swap(f, g);
        swap(fr, nfr);
    }
    ans_r[mid] = fr[t];

    if (l == 0 && r == n) // first dp, save the ans
        ans = f[t];

    dp(l, mid, s, ans_r[mid]);
    dp(mid, r, ans_r[mid], t); 
}

int main() {
    cin >> n >> V;
    for (int i = 1; i <= n; ++i)
        cin >> num[i] >> volume[i] >> value[i];

    reverse(num + 1, num + n + 1);
    reverse(volume + 1, volume + n + 1);
    reverse(value + 1, value + n + 1);

    ans_r[0] = 0, ans_r[n] = V;
    dp(0, n, 0, V);

    cout << ans << endl;
    for (int i = n; i >= 1; --i) {
        cout << (ans_r[i] - ans_r[i-1]) / volume[i];

        ans -= (ans_r[i] - ans_r[i-1]) / volume[i] * value[i];

        if (i != 1)
            cout << " ";
        else
            cout << endl;
    }
}
