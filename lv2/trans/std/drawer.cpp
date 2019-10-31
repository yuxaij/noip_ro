#include <cmath>
#include <iostream>
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
        std::cerr << "fin powdrawer init." << std::endl;
    }
    void draw(int n, int m, int minp, int maxp, int *p, int n_parts = 0, const int *part_sizes = nullptr, const double *part_powes = nullptr) {
        /*
            draw m times and save the results to p[1..n]
            guarantee that p[i] \in [minp, maxp]
        */
        
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
            std::cerr << "drawer round: " << i << std::endl;
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

const int n_parts[] = {
    5, 5
};

const int part_sizes[][5] = {
    {1, 1, 1, 1, 1},
    {20, 15, 15, 15, 15}
};
const double part_powes[][5] = {
    {0.4, 0.5, 0.6, 0.7, 0.8},
    {-100, 0.45, 0.55, 0.65, 0.75}
};
