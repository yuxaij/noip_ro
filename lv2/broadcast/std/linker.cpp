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
int vis[MAXN + 10];

bool mark[MAXN + 10];
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

        int lt = qt;
        int merged = 0;
        while (lt > 0) {
            while (lt > 0 && rig[lt] < cur_l)
                lt = vis[lt];

            if (lt > 0 && cur_lef <= r[lt]) {
                cur_lef = min(cur_lef, lef[lt]);
                cur_rig = max(cur_rig, rig[lt]);
                cur_l = l[lt];

                max_ans += qt - lt;
                qt = lt - 1;
                lt = vis[lt];
            }
            else break;    
        }

        ++qt;
        lef[qt] = cur_lef;
        rig[qt] = cur_rig;
        l[qt] = cur_l;
        r[qt] = x;
        vis[qt] = lt;
    }
    int rigp = int(-1e9);
    for (int i = 1; i <= qt; ++i) {
        if (rigp >= l[i])
            mark[i] = true;
        rigp = max(rig[i], rigp);
    }

    int lefp = int(~0U>>1);
    for (int i = qt; i >= 1; --i) {
        if (lefp <= r[i])
            mark[i] = true;
        lefp = min(lef[i], lefp);
    }
    max_ans += qt;
    min_ans = count(mark + 1, mark + qt + 1, false); 
    cout << min_ans << " " << max_ans << endl;
}
