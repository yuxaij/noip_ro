#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

void link(int a, int b, int low, int high, bool is_in_spt = false) {
    ++ap;
    start[ap] = a;
    end[ap] = b;
    val[ap] = rand() % (high - low + 1) + low;

    if (is_in_spt)
        dis[b] = dis[a] + val[ap];
    else 
        val[ap] += dis[b] - dis[a];
}
void spfa_killer(int n, int *nodes, int m, int low, int high) {
    if (lvs > n) {
    }
    if (m < n-1) {
    }

    11111111111111111111111111111111

    +
} 
void levelized(int n, int *nodes, int m, int low, int high, int lvs=5) {
    if (lvs > n) {
        cerr << "levelized error: lvs " << lvs " > " << n << endl; 
        exit(0);
    }
    if (m < n-1) {
        cerr << "levelized error: m " << m " < " << n - 1 << endl;
        exit(0);
    }

    int *p = (int*) malloc(sizeof(int) * n + 1);
    for (int i = 0; i <= n; ++i)
        p[i] = i;

    random_shuffle(p + 2, p + n + 1);
    sort(p + 2, p + lvs + 1);

    p[lvs] = n;
    p[lvs - 1] = n - 1;

    long long cnt = 0;
    map <int, int> rdm;
    for (int i = 1; i < lvs; ++i) { // between i, i+1 
        int a = p[i-1], b = p[i], c = p[i+1]; 

        // offset [a+1,b+1) +i
        // offset [b+1,c+1) +i+1
        
        for (int j = b; j < c; ++j) {
            int f = nodes[rand() % (b - a) + a + 1];
            
            link(f, nodes[j + 1], low, high, true); 
        } 
        cnt += (long long) (c - b) * (b - a);
        rdm[cnt] = i;  
    }
    int r = (p[lvs - 1] - p[lvs - 2]) - 1;
    for (int i = n; i <= m; ++i) {
        long long r = ((rand() << 32) | rand()) % cnt + 1;
        int loc = rdm.lower_bound(r)->second;
        int a = p[loc - 1], b = p[loc], c = p[loc + 1];

        int v = rand() % (b - a) + a + 1; 
        int u = rand() % (c - b) + b + 1;
        
        if (r != 0) {
            v = nodes[p[lvs - 1] - (r--)];
            u = nodes[n];
        }

        if (dis[v] > dis[u])
            swap(u, v);
        link(u, v, 0, 1);
    }
}
void random(int n, int *nodes, int m, int low, int high, int fn=5) {
    if (m < n-1) {
        cerr << "random error: m " << m << " < " << n-1 << endl;
        exit(0);
    }
    int *p = (int*) malloc(sizeof(int) * n + 1);
    for (int i = 2; i <= n; ++i) {
        int f = i - 1 - rand() % min(fn, i - 1);
        link(nodes[i], nodes[f], low, high, true);
        p[f] = true;
        p[i] = false;
    }
    int cnt = 0;
    for (int i = 1; i < n; ++i)
        if (p[i] == false)
            p[++cnt] = i;

    random_shuffle(p + 1, p + cnt + 1);
    for (int i = n; i <= m; ++i) {
        int a = nodes[rand() % n + 1];
        int b = nodes[rand() % n + 1];

        if (cnt != 0)
            a = nodes[n], b = nodes[p[cnt--]];

        if (dis[a] > dis[b])
            swap(a, b);

        link(a, b, 1, 1); 
    }
    free(p);
}
int main() {
    for (int i = 1; i <= n; ++i) {
    }
}
