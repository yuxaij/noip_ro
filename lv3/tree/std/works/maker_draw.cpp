#include <map>
#include <ctime>
#include <cmath>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm>
#define PATH_GEN 0
#define SINGLE_PATH_GEN 1
const int MAXN = int(1e5);
const int MAXPI = 20;
using namespace std;

vector<int> ads[MAXN + 10];

int dfs_pos[MAXN + 10];
int dfs_pos_out[MAXN + 10];
int dfs_pos_t;

int father[MAXN + 10];
int depth[MAXN + 10];
int parent[MAXN + 10][MAXPI];

vector<int> qs[MAXN + 10];
int qs_t;

map <int, int> bfs_q;
int bfs_Y;
int vis[MAXN + 10];

int leaves[MAXN + 10];
int n_leaves;

int mark[MAXN + 10];

int a[MAXN + 10];
int b[MAXN + 10];

void clear() {
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(father, 0, sizeof(father));
    memset(parent, 0, sizeof(parent));
    memset(dfs_pos, 0, sizeof(dfs_pos));
    memset(dfs_pos_out, 0, sizeof(dfs_pos_out));
    memset(leaves, 0, sizeof(leaves));
    memset(vis, 0, sizeof(vis));
    memset(mark, 0, sizeof(mark));

    bfs_Y = 0;
    n_leaves = 0;
    qs_t = 0;
    dfs_pos_t = 0;

    bfs_q.clear();

    for (int i = 1; i <= MAXN; ++i)
        ads[i].clear();
}

void link(int a, int b) {
    ads[a].push_back(b);
    ads[b].push_back(a);
}
bool cmp_vt_rank(const int &a, const int &b) {
    return dfs_pos[a] < dfs_pos[b];
}
void dfs(int z, int ft) {
    depth[z] = depth[ft] + 1;
    father[z] = ft;
    parent[z][0] = father[z];
    for (int i = 1; i < MAXPI; ++i)
        parent[z][i] = parent[parent[z][i-1]][i-1];

    dfs_pos[z] = ++dfs_pos_t;
    for (auto &x : ads[z])
        if (x != ft) {
            dfs(x, z);
        }
    dfs_pos_out[z] = dfs_pos_t;
}
inline bool is_in_sub_tree(int a, int root) {
    return dfs_pos[a] >= dfs_pos[root] && dfs_pos[a] <= dfs_pos_out[root];
}
int random_node_from(int a, int b) {
    if (a == b)
        return a;
    //cerr << "abs random: " << abs(depth[a] - depth[b]) << endl;
    if (is_in_sub_tree(a, b)) {
        int d = rand() % (depth[a] - depth[b]);
        //cerr << "random: " << d << endl;
        for (int i = MAXPI; i--; )
            if (d & (1<<i))
                a = parent[a][i];
        return a;
    }
    else if (is_in_sub_tree(b, a)) {
        int d = rand() % (depth[b] - depth[a]) + 1;
        //cerr << "random: " << d << endl;
        for (int i = MAXPI; i--; )
            if (d & (1<<i))
                b = parent[b][i];
        return b;
    }
    else {
        cerr << "random node from error: not parent relation. node " << a << " and " << b << "." << endl;
        exit(0);
    }
}
int get_lca(int x, int y) {
    if (x == 0) return y;
    if (y == 0) return x;
    if (x == y) return x;
    if (depth[x] < depth[y])
        swap(x, y);
    for (int i = MAXPI; i--; )
        if (depth[parent[x][i]] >= depth[y])
            x = parent[x][i];
    if (x == y) return x;
    for (int i = MAXPI; i--; )
        if (parent[x][i] != parent[y][i])
            x = parent[x][i], y = parent[y][i];
    return father[x];
}

int rand_path_by_step(int L, int z, int fr = 0) {
    if ((ads[z].size() == 1 && fr != 0) || L == 0)
        return z;

    int p;
    do {
        p = rand() % (L * ads[z].size() + 1);
    }
    while (p != 0 && fr != 0 && ads[z][(p - 1) / L] == fr);
    if (p == 0)
        return z; 
    return rand_path_by_step(L - 1, ads[z][(p - 1) / L], z);
}

struct VirtualTree {
    int n; 
    int nodes[MAXN + 10];
    int father[MAXN + 10];
    int qs[MAXN + 10];
    int Y;

    int vis[MAXN + 10];
    int cst[MAXN + 10];
    int ls[MAXN + 10];
    int cs[MAXN + 10];

    vector<int> ads[MAXN + 10];
    VirtualTree() {
        n = 0;
        for (int i = 0; i <= MAXN; ++i)
            nodes[i] = 0;
        for (int i = 0; i <= MAXN; ++i)
            ads[i].clear();
        for (int i = 0; i <= MAXN; ++i)
            vis[i] = cst[i] = ls[i] = cs[i] = 0;
    }
    void build(int n, int *nodes) {
        int lca = 0;
        for (int i = 1; i <= n; ++i)
            lca = get_lca(nodes[i], lca);

        sort(nodes + 1, nodes + n + 1, cmp_vt_rank);
        n = unique(nodes + 1, nodes + n + 1) - nodes - 1;

        if (nodes[1] != lca)
            nodes[0] = lca, --nodes, ++n;

        int n_ls = 0;
        int n_cs = 0;
        int qs_t = 0;
        int n_nodes = 0;
        for (int i = 1; i <= n; ++i) {
            int lca = 0;
            while (qs_t > 0 && !is_in_sub_tree(nodes[i], qs[qs_t])) {
                lca = get_lca(nodes[i], qs[qs_t]);

                if (cst[qs[qs_t]] == 1)
                    ls[++n_ls] = qs[qs_t];
                if (cst[qs[qs_t]] >= 3)
                    cs[++n_cs] = qs[qs_t];

                --qs_t;
            }
            if (lca == 0)
                lca = qs[qs_t];
            if (vis[lca] < Y)
                vis[lca] = Y, cst[lca] = 0;

            if (qs_t > 0 && lca == qs[qs_t])
                cst[lca] += 1;
            else if (lca != 0)
                cst[lca] = 3, qs[++qs_t] = lca;

            vis[nodes[i]] = Y;
            cst[nodes[i]] = qs_t > 0;

            qs[++qs_t] = nodes[i];
        }
        for (int i = 1; i <= qs_t; ++i)
            if (cst[qs[i]] == 1)
                ls[++n_ls] = qs[i];
            else if (cst[qs[i]] >= 3)
                cs[++n_cs] = qs[i];

        if (n == 1)
            ls[++n_ls] = qs[qs_t];

        ls[0] = n_ls;
        cs[0] = n_cs;

        nodes = this->nodes;

        for (int i = 1; i <= n_ls; ++i)
            nodes[++n_nodes] = ls[i];
        for (int i = 1; i <= n_cs; ++i)
            nodes[++n_nodes] = cs[i];

        nodes[++n_nodes] = lca;
        sort(nodes + 1, nodes + n_nodes + 1, cmp_vt_rank);
        n_nodes = unique(nodes + 1, nodes + n_nodes + 1) - nodes - 1;

        qs_t = 0;
        qs[qs_t] = 0;
        for (int i = 1; i <= n_nodes; ++i) {
            while (qs_t > 0 && !is_in_sub_tree(nodes[i], qs[qs_t]))
                --qs_t;

            if (qs_t > 0) {
                ads[nodes[i]].push_back(qs[qs_t]);
                ads[qs[qs_t]].push_back(nodes[i]);
            }

            father[nodes[i]] = qs[qs_t];
            qs[++qs_t] = nodes[i];

        }

        this->n = n_nodes;
    } 
} *whole_vt = new VirtualTree(), *leaves_vt = new VirtualTree();

struct DrawerNode {
    int l, r, mid;
    long long sum;

    DrawerNode *lef, *rig;
    DrawerNode(int l, int r) {
        this->l = l;
        this->r = r;
        this->mid = (l + r) >> 1;
        this->sum = r - l + 1;

        if (l == r)
            return;

        this->lef = new DrawerNode(l, mid);
        this->rig = new DrawerNode(mid + 1, r);
    }
    void clean(int n) {
        if (n < l)
            this->sum = 0;
        else if (n < r)
            this->sum = n - l + 1;
        else
            this->sum = r - l + 1;
        if (l == r)
            return;

        lef->clean(n);
        rig->clean(n);
    }
    void update(int x, int v) {
        if (l == r) {
            if (v == -1)
                this->sum = 0;
            else
                this->sum += v;
            return;
        }

        if (x <= mid)
            lef->update(x, v);
        else
            rig->update(x, v);
        this->sum = lef->sum + rig->sum;
    }
    int query(long long x) {
        if (l == r)
            return l;
        if (lef->sum >= x)
            return lef->query(x);
        else
            return rig->query(x - lef->sum);
    }
};

struct PowDrawer {
    DrawerNode *root;
    int max_size;

    const int default_n_parts = 2;
    const int default_part_sizes[2] = {1, 1};
    const double default_part_powes[2] = {0.5, 0.8};

    PowDrawer(int max_size) {
        this->max_size = max_size;
        this->root = new DrawerNode(1, max_size); 
    }
    void draw(int n, int m, int minp, int maxp, int *p, int n_parts = 0, const int *part_sizes = nullptr, const double *part_powes = nullptr) {
        if (n_parts == 0)
            n_parts = this->default_n_parts;
        if (part_sizes == nullptr)
            part_sizes = this->default_part_sizes;
        if (part_powes == nullptr)
            part_powes = this->default_part_powes;            
        
        for (int i = 1; i <= n; ++i)
            p[i] = minp;

        m -= minp * n;

        if (m < 0) {
            fprintf(stderr, "drawer error: %dx%d > %d\n", minp, n, m + minp * n);
            exit(0);
        }

        int part_sizes_all = 0;

        for (int i = 0; i < n_parts; ++i)
            part_sizes_all += part_sizes[i];

        int tot_k = 0;
        for (int i = 0; i < n_parts; ++i) {
            int k = (double) part_sizes[i] / part_sizes_all * m;
            tot_k += k;
            if (i == n_parts - 1)
                k += m - tot_k, tot_k = m;

            root->clean(n);

            for (int i = 1; i <= n; ++i)
                if (p[i] == maxp)
                    root->update(i, -1);

            for (int j = k - 1; j >= 0; --j) {
                int v = pow(j, part_powes[i]);
                int t = root->query(rand() % root->sum + 1);
                p[t] += 1;
                root->update(t, v);

                if (p[t] >= maxp)
                    root->update(t, -1);
            }
        }
    }
} *drawer = new PowDrawer(int(1e6));

void gen_tree(int n, int m, bool use_all_n, int n_parts = 2, const int *sizes = nullptr, const double *powes = nullptr) {
    int *p = (int*) malloc(sizeof(int) * (n + 10));

    drawer->draw(n, m, use_all_n, m, p, n_parts, sizes, powes);

    cerr << "gen_tree: drawer fin" << endl;

    sort(p + 1, p + n + 1);
    reverse(p + 1, p + n + 1);

    while (p[n] == 0)
        --n;

    //random_shuffle(p + 1, p + n + 1);

    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        int last = i == 1 ? 0 : rand() % cnt + 1;
        for (int j = 1; j <= p[i]; ++j) {
            ++cnt;
            if (last != 0) link(last, cnt);
            last = cnt;
        } 
    }
    dfs(cnt, 0);
    free(p);
    cerr << "gen_tree: dfs fin" << endl;

    p = (int*) malloc(sizeof(int) * (m + 10));
    for (int i = 1; i <= m; ++i)
        p[i] = i;

    whole_vt->build(m, p); 
    free(p);
    cerr << "gen_tree: whole_vt build. ls=" << whole_vt->ls[0] << ", cs=" << whole_vt->cs[0] << endl;

    for (int i = 1; i <= whole_vt->ls[0]; ++i)
        leaves[i] = whole_vt->ls[i];
    n_leaves = whole_vt->ls[0]; 
}
void random_leaf_saver(int n_saves) {
    qs[++qs_t].clear();
    random_shuffle(leaves + 1, leaves + n_leaves + 1);

    leaves_vt->build(n_saves, leaves);
    
    for (int i = 1; i <= n_saves; ++i) { 
        if (n_saves == 1) {
            qs[qs_t].push_back(rand() % dfs_pos_t + 1);
            break;
        }

        int f = leaves_vt->father[leaves[i]];
        if (f == 0) 
            f = leaves_vt->ads[leaves[i]][0];

        int t = random_node_from(leaves[i], f);
        qs[qs_t].push_back(t);
    }
}
/*
void virtual_node_bfser(int n_nodes) {
    qs[++qs_t].clear();
    bfs_q.clear();

    bfs_Y += 4;

    int no_t = 0;
    int t;
    while (n_nodes != 0) {
        no_t++;
        if (no_t == 1)
            t = whole_vt->cs[rand() % whole_vt->cs[0] + 1];
        else {
            t = bfs_q.begin()->second;
            bfs_q.erase(bfs_q.begin());
        }
        --n_nodes;
        vis[t] = bfs_Y;
        for (auto node : whole_vt->ads[t])
            if (vis[node] < bfs_Y)
                bfs_q[rand()] = node; 
            else {
                vis[t]++;
                if ((vis[node] & 3) == 3)
                    continue;
                else if ((vis[node] & 2))
                    ++n_nodes, ++vis[node];
                else
                    ++vis[node]; 
            }
    }
    for (int i = 1; i <= whole_vt->n; ++i) {
        int node = whole_vt->nodes[i];
        if (vis[node] >= bfs_Y) {
            cerr << node << " " << (vis[node] & 3) << endl;
            if ((vis[node] & 3) == 3)
                continue;
            if ((vis[node] & 2)) {
                int p = rand() % (whole_vt->ads[node].size() - 2) + 1;
                for (auto noda : whole_vt->ads[node])
                    if (vis[noda] < bfs_Y) {
                        --p;
                        if (p == 0) {
                            qs[qs_t].push_back(random_node_from(noda, node));
                            break;
                        }
                    }
            }
            else if ((vis[node] & 1)) {
                for (auto noda : whole_vt->ads[node])
                    if (vis[noda] >= bfs_Y) {
                        qs[qs_t].push_back(random_node_from(node, noda));
                        break;
                    }
            }
            else {
                qs[qs_t].push_back(node);
            }
        }
    }
}
*/
void gen_queries(int mode, int m, int k, int maxk, int n_parts = 2, const int *sizes = nullptr, const double *powes = nullptr) {
    qs_t = 0;
    int *p = (int*) malloc(sizeof(int) * (m + 10));

    drawer->draw(m, k, 1, maxk, p, n_parts, sizes, powes);

    random_shuffle(p + 1, p + m + 1);

    for (int i = 1; i <= m; ++i) {
        if (i % (m / 5) == 0)
            cerr << "query " << i << " done." << endl;
        if (mode == PATH_GEN)
            random_leaf_saver(p[i]);
        else if (mode == SINGLE_PATH_GEN)
            random_leaf_saver(2);
    }
    free(p);
}
void dfs_marker(int z, int ft) {
    for (auto x : ads[z])
        if (x != ft)
            dfs_marker(x, z), mark[z] += mark[x];
}
void gen_oprs(int m1, int m2, int L) {
    int n = dfs_pos_t;
    int cr = 0;
    int *r = (int*) malloc(sizeof(int) * (n+10));
    int *q = (int*) malloc(sizeof(int) * (n+10));
    for (int i = 1; i <= m1; ++i) {
        int ct = 0;
        for (auto s : qs[i])
            r[++ct] = s;
        
        leaves_vt->build(ct, r);
        int q_t = 0;
        for (int i = 1; i <= leaves_vt->n; ++i) {
            int node = leaves_vt->nodes[i];
            while (q_t > 0 && !is_in_sub_tree(node, q[q_t]))
                --q_t;

            if (q_t == 0)
                mark[parent[node][0]]--;
            else
                mark[leaves_vt->father[node]]--;
        
            mark[node]++;
        }
    }
    dfs_marker(n, 0);

    DrawerNode *root = new DrawerNode(1, n);
    for (int i = 1; i <= n; ++i)
        root->update(i, mark[i] - 1);

    int *p = (int*) malloc(sizeof(int) * (m2+10));
    for (int i = 1; i <= m2; ++i)
        p[i] = i;

    long long toal = 0;
    for (int i = 1; i <= m2; ++i) {
        long long v = ((((long long) rand()) << 32) + rand()) % root->sum + 1;    
        int t = root->query(v);
        int s = rand_path_by_step(L, t);
        a[p[i]] = t;
        b[p[i]] = s;
        toal += mark[t];
    }
    free(p);
    cerr << "total involved pathes(estimated): " << toal << endl;
}
void gen_data(const char *file_name, int mode, int n, int nn, bool use_all_nn, int m1, int m2, int k, int v_low, int v_high, int L,  
    int query_n_parts = 2, const int *query_sizes = nullptr, const double *query_powes = nullptr,
    int chain_n_parts = 2, const int *chain_sizes = nullptr, const double *chain_powes = nullptr) {
    clear();
    ofstream gout(file_name);

    gen_tree(nn, n, use_all_nn, chain_n_parts, chain_sizes, chain_powes); 
    cerr << "tree finished." << endl;

    gen_queries(mode, m1, k, whole_vt->ls[0], query_n_parts, query_sizes, query_powes); 
    cerr << "query finished." << endl;

    gen_oprs(m1, m2, L);
    cerr << "oprs finished." << endl;

    gout << n << " " << m1 + m2 << " " << L << endl;

    int *p = (int*) malloc(sizeof(int) * (n+10));
    int *q = (int*) malloc(sizeof(int) * (m1 + m2 +10));
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
        swap(p[i], p[rand() % i + 1]);
    }

    for (int i = 1; i <= n; ++i) {
        for (auto j : ads[i]) {
            if (j < i)
                if (rand() & 1)
                    gout << p[i] << " " << p[j] << endl;
                else
                    gout << p[j] << " " << p[i] << endl;
        }
    }

    for (int i = 1; i <= m1 + m2; ++i)
        q[i] = i;

    random_shuffle(q + 1 + m2 / 2, q + m1 + m2 + 1);
    sort(q + 1, q + m2 + 1);
    for (int i = m2; i >= 1; --i)
        q[q[i]] = -1;
    
    int cr = 0;
    int *r = (int*) malloc(sizeof(int) * (n+10));
    long long toal = 0;
    int cw = 0;
    for (int i = 1; i <= m1 + m2; ++i) {
        if (q[i] != -1) {
            int ct = 0;
            ++cr;
            for (auto s : qs[cr])
                r[++ct] = s;
            leaves_vt->build(ct, r);

            for (int j = 2; j <= leaves_vt->n; ++j)
                toal += depth[leaves_vt->nodes[i]] - depth[leaves_vt->father[leaves_vt->nodes[i]]];
            toal++;

            gout << "1";
            gout << " " << leaves_vt->ls[0];
            for (int j = 1; j <= leaves_vt->ls[0]; ++j)
                gout << " " << p[leaves_vt->ls[j]];
            gout << " " << leaves_vt->cs[0];
            for (int j = 1; j <= leaves_vt->cs[0]; ++j)
                gout << " " << p[leaves_vt->cs[j]];

            gout << endl;
        }
        else {
            ++cw;
            gout << "0 " << p[a[cw]] << " " << p[b[cw]] << " " << v_low + rand() % (v_high - v_low + 1) << endl;
        }
    }
    free(p);
    free(q);
    free(r);

    cerr << "total involved nodes " << toal << endl;

    gout.close();
}

const int n_parts[] = {
    5, 5
};

const int sizes[][5] = {
    {1, 1, 1, 1, 1},
    {20, 15, 15, 15, 15}
};
const double powes[][5] = {
    {0.4, 0.5, 0.6, 0.7, 0.8},
    {-100, 0.45, 0.55, 0.65, 0.75}
};
/*
int main(int argc, char **argv) {
    srand((unsigned)time(NULL));
    gen_data(0, PATH_GEN, 100000, 10000, true, 50000, 50000, 100000 * 5, int(9e4), int(1e5), 
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    gen_data("test.in", SINGLE_PATH_GEN, 20, 10, true, 20, 20, 20*3, 0, 100, 0, 
        n_parts[0], sizes[0], powes[0], n_parts[0], sizes[0], powes[0]);
}
*/
