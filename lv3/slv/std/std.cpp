#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
const int MAXN = int(1e5);
const int MAXM = int(1e5);
const int MAXE = MAXM * 20;
const int INF = (~0U>>1);

int g[MAXN + 10];
int c[2*MAXE + 10], next[2*MAXE + 10];
int ap = 1;

int a[MAXM + 10], b[MAXM + 10], v[MAXM + 10];
int p[MAXM + 10];

int father[MAXN + 10];
int rank[MAXN + 10];
int erase_t[MAXN + 10];

struct hash_list {
    int g[11229331];
    int a[MAXE + 10], b[MAXE + 10], t[MAXE + 10];
    int next[MAXE + 10];
    int ap;

    hash_list() {
        memset(g, 0, sizeof(g));
        memset(next, 0, sizeof(next));
        ap = 0;
    }
    int hash(int a, int b) {
        return ((unsigned) (a * MAXN + b)) % 11229331;
    }
    bool find_edge_before_t(int a, int b, int occur_t) {
        if (a > b)
            std::swap(a, b);
        for (int x = g[hash(a, b)]; x; x = next[x])
            if (this->a[x] == a && this->b[x] == b)
                return t[x] <= occur_t;
        return false;
    }
    void new_edge(int a, int b, int occur_t) {
        if (a > b)
            std::swap(a, b);
        int &x = g[hash(a, b)];
        this->a[++ap] = a;
        this->b[ap] = b;
        this->t[ap] = occur_t;
        
        next[ap] = x;
        x = ap;
    }
} ht;

void link(int a, int b, int occur_t) {
    if (a == b || ht.find_edge_before_t(a, b, occur_t) == true)
        return;

    c[++ap] = b, next[ap] = g[a], g[a] = ap; 
    c[++ap] = a, next[ap] = g[b], g[b] = ap;
    
    ht.new_edge(a, b, occur_t);
}
int get_c(int a, int t) {
    while (father[a] != a && erase_t[a] <= t)
        a = father[a];
    return a;
}
bool cmp(const int &a, const int &b) {
    return v[a] < v[b];
}
int main() {
    int n, m, q;

    std::cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i) {
        father[i] = i;
        erase_t[i] = INF;
        rank[i] = 1;
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d", a + i, b + i, v + i);
        link(a[i], b[i], 0);
        p[i] = i;

        rank[a[i]]++;
        rank[b[i]]++;
    }
    std::sort(p + 1, p + m + 1, cmp);
    for (int i = 1; i <= m; ++i) {
        int nt = p[i];
        
        int ca = get_c(a[nt], i);
        int cb = get_c(b[nt], i);

        if (ca == cb) 
            continue;

        if (rank[ca] < rank[cb])
            std::swap(ca, cb);

        rank[ca] += rank[cb];
        father[cb] = ca;   
        erase_t[cb] = i;

        for (int x = g[cb]; x; x = next[x])
            if (erase_t[c[x]] == INF)
                link(ca, c[x], i); 
    }
    for (int i = 1; i <= q; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        int l = 0, r = m, j, an = -1;
        for (; j = (l + r) >> 1, l <= r; ) { 
            int ca = get_c(a, j);
            int cb = get_c(b, j);
            if (ca == cb || ht.find_edge_before_t(ca, cb, j) == true) 
                an = j, r = j - 1;
            else
                l = j + 1;
        }
        if (an == -1)
            std::cout << -1 << std::endl;
        else
            std::cout << v[p[an]] << std::endl;
    }
}
