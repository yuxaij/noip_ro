#include <cstdio>
#include <iostream>
#include <algorithm>
const int MAXL = int(1e6);
const int MAXV = int(1e9);
using namespace std;

int v[MAXL + 10];
int rk[MAXL + 10];
int p[MAXL + 10];
int q[MAXL + 10];

bool cmp(const int &a, const int &b) {
    return v[a] < v[b] || (v[a] == v[b] && a < b);
}
int main() {
    int type, n, k, m, a, b;
    cin >> n >> k >> m;
    cout << n << " " << k << " " << m << endl;
    for (int i = 1; i < n; ++i) {
        cin >> a >> b;
        cout << a << " " << b << endl;
    }
    for (int i = 1; i <= k; ++i) {
        cin >> p[i] >> q[i] >> v[i];
        rk[i] = i;
    }
    sort(rk + 1, rk + k + 1, cmp);

    bool is_unique = true;
    for (int i = 2; i <= k; ++i)
        if (v[rk[i]] == v[rk[i-1]])
            is_unique = false;

    int retvalue = 0;
    if (is_unique == false) {
        for (int i = 1; i <= k; ++i) {
            v[rk[i]] += i - 1;
        }
        if (v[rk[k]] > MAXV) {
            cerr << "fail to uniquilize v[]." << endl;
            for (int i = 1; i <= k; ++i)
                v[rk[i]] -= i - 1;
            retvalue = 1;
        }
    }
    else {
        cerr << "v[] is unique." << endl;
    }

    for (int i = 1; i <= k; ++i)
        cout << p[i] << " " << q[i] << " " << v[i] << endl;

    for (int i = 1; i <= m; ++i) {
        cin >> type;
        if (type == 0)
            cout << type << endl;
        else
            cin >> a, cout << type << " " << a << endl;
    }
}
