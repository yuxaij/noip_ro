#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const int MAXN = int(1e6);
using namespace std;

int tmpi;
char tmpc;
bool tmps;

int rig[MAXN + 10], r[MAXN + 10];
int lef[MAXN + 10], l[MAXN + 10];

int q[MAXN + 10];
int qt; 

int getint() {
    while (tmpc = getchar(), tmpc != '-' && (tmpc < '0' || tmpc > '9'));
    tmps = tmpc == '-' ? (tmpc = getchar(), 1) : 0;
    tmpi = 0;
    while (tmpc >= '0' && tmpc <= '9')
        tmpi = tmpi * 10 + tmpc - '0', tmpc = getchar();
    return tmps ? -tmpi : tmpi;
}
int main() {
    int n;
    int max_ans = 0;
    int min_ans = 0;

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x = getint();
        int d = getint();

        int cur_l = x;
        int cur_rig = x + d;
        int cur_lef = x - d;
        while (qt > 0 && cur_lef <= r[qt]) {
            if (rig[qt] >= cur_l)
                cur_l = l[qt], cur_rig = max(cur_rig, rig[qt]); 
            else ++max_ans;

            --qt;
        }
        ++qt;
        rig[qt] = cur_rig, lef[qt] = cur_lef;
        l[qt] = cur_l, r[qt] = x;
    }
    max_ans += qt;

    int rigp = int(-1e9);
    for (int i = 1; i <= qt; ++i) {
        if (rigp < l[i])
            ++min_ans;
        rigp = max(rig[i], rigp);
    }
    cout << min_ans << " " << max_ans << endl;
}
