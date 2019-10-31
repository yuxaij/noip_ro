#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const int MAXN = 100000; 
using namespace std;

int n;
int cnt[MAXN + 10];

struct node {
    node *lef, *rig;
    int l, r, sum;

    node(int l, int r) {
        this->sum = r - l + 1;
        this->l = l;
        this->r = r;
        if (l == r)
            return;
        
        int mid = (l+r)>>1;
        this->lef = new node(l, mid);
        this->rig = new node(mid+1, r);
    }
    void update(int x, int v) {
        sum += v;
        if (l == r)
            return;
        if (x <= ((l+r)>>1))
            this->lef->update(x, v);
        else
            this->rig->update(x, v);
    }
    int query(int x) {
        if (l == r)
            return l;
        if (this->lef->sum < x)
            return this->rig->query(x - this->lef->sum);
        else
            return this->lef->query(x);
    }
};

int main(int argc, char **argv) { 
    srand((unsigned)time(NULL));
    
    sscanf(argv[1], "%d", &n);

    node *root = new node(1, n);
 
    for (int i = n; i >= 1; --i) {
        int pos = rand() % root->sum + 1;
        int t = root->query(pos);
        root->update(t, int(pow(i, 0.8)+1));
        //root->update(t, i);
        
        cnt[t]++;
    }
    sort(cnt + 1, cnt + n + 1);
    for (int i = 1; i <= n; ++i)
        cout << cnt[i] + 3 << " ";
    cout << endl; 
}
