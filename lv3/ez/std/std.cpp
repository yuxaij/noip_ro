#include <set>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const int MAXN = 600;
using namespace std;

struct Scheme {
    int value;
    int pos[MAXN + 10];
};
struct cmp {
    bool operator () (const Scheme *a, const Scheme *b) {
        return a->value < b->value || a->value == b->value && a < b;
    }
};
set <Scheme*, cmp> q;

int n;
int v[MAXN + 10][MAXN + 10];

Scheme scheme[MAXN + 10];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j)
                scanf("%d", v[i] + j);
            sort(v[i] + 1, v[i] + n + 1);
        }

        int start_value = 0;
        for (int i = 1; i <= n; ++i)
            start_value += v[i][1];

        cout << start_value;
        
        q.clear();
        for (int i = 1; i <= n; ++i) {
            auto t = scheme + i;
            t->value = start_value;
            for (int j = 1; j <= n; ++j)
                t->pos[j] = 1;
            t->pos[i] = 2;
            t->value += v[i][2] - v[i][1];
            q.insert(t);
        }
        for (int i = 2; i <= n; ++i) {
            auto t = *q.begin(); 
            printf(" %d", t->value);
            q.erase(q.begin());

            if (i == n)
                break;

            for (int j = n; j >= 1; --j) {
                if (t->pos[j] != n) {
                    int new_value = t->value + v[j][t->pos[j] + 1] - v[j][t->pos[j]];
                
                    auto otp = --q.end();
                    auto nt = *otp;
                    if (nt->value > new_value) {
                        q.erase(otp);
                        for (int k = 1; k <= n; ++k)
                            nt->pos[k] = t->pos[k];
                        nt->pos[j] ++;
                        nt->value = new_value;
                        q.insert(nt);
                    }
                }
                if (t->pos[j] > 1)
                    break;
            }
        }
        cout << endl;
    }
}
