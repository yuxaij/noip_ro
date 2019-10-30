#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define SAME 1
#define PRIME 2
#define NONE 0
const int MAXP = int(1e7);
using namespace std;

int prime[MAXP + 10];
int phi[MAXP + 10];
int fr[MAXP + 10];
int pcnt;

int prs[110], times[110], cnt;
int prs_phi[110], times_phi[110], cnt_phi; 

int pa[MAXP + 10], pb[MAXP + 10], pc[MAXP + 10], pd[MAXP + 10];
int pt;

int gcd(int a, int b) {
    int t;
    while (a)
        t = a, a = b % a, b = t; 
    return b;
}
int ex(int a, int p, int b) {
    if (a == 0)
        return b == 0 ? 0 : -1; 

    b = (b % p + p) % p;
    int t = ex(p % a, a, -b); 
    return t == -1 ? t : ((long long) p * t + b) / a;
}
void get_primes(int p, int *prs, int *times, int &cnt) {
    cnt = 0;
    while (p != 1) {
        prs[++cnt] = p / fr[p];
        times[cnt] = 0;
            
        while (p % prs[cnt] == 0)
            p /= prs[cnt], ++times[cnt]; 
    }
}
int fpm(int a, int b, int p) {
    long long r = 1;
    for (; b; b >>= 1, a = (long long) a * a % p)
        if (b & 1)
            r = r * a % p;
    return r;
}
int try_to_find(int power, int p) {
    int rs = min(10000, p);
    for (int i = 2; i < rs; ++i)
        if (fpm(i, power, p) == 1)
            return i;
    return -1;
}
int try_prime(int p) {
    int ret = 1;
    if (p < 20) {
        for (int i = 2; i <= p; ++i)
            if (gcd(i, p) == 1)
                if (ret == 1 || (rand() & 1))
                    ret = i;
    }
    else {
        while (true) {
            ret = rand() % p + 1;
            if (ret != 1 && gcd(ret, p) == 1)
                break;
        }
    }
    return ret;                
}
int try_fac(int x) {
    int ret = 1;
    get_primes(x, prs, times, cnt);
    for (int i = 1; i <= cnt; ++i) {
        for (int j = rand() % (times[i] + 1); j >= 1; --j)
            ret *= prs[j];
    }
    if (ret == x)
        ret /= prs[rand() % cnt + 1];
    return ret;
}
int main(int argc, char **argv) {
    int maxp, q, mode;
    sscanf(argv[1], "%d", &q);
    sscanf(argv[2], "%d", &maxp);
    sscanf(argv[3], "%d", &mode);

    time_t tn = time(NULL);
    srand((unsigned)tn);

    phi[1] = 0;
    for (int i = 2; i <= maxp; ++i) {
        if (prime[i] != -1)
            prime[++pcnt] = i, phi[i] = i - 1, fr[i] = 1; 
        for (int j = 1; j <= pcnt; ++j) {
            if (i > MAXP / prime[j]) 
                break;

            prime[i * prime[j]] = -1;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                fr[i * prime[j]] = i;
                break;
            }
            else phi[i * prime[j]] = phi[i] * (prime[j] - 1), fr[i * prime[j]] = i;
        }
    }
    FILE *hack_list = fopen("hack_list.txt", "r");
    int n_hacks;
    int a1, a2, a3, a4, a0;

    while (fscanf(hack_list, "%d %d %d %d %d", &a0, &a1, &a2, &a3, &a4) != EOF) {
        if (a2 <= maxp) {
            ++n_hacks;
            pa[n_hacks] = a1;
            pb[n_hacks] = a2;
            pc[n_hacks] = a3;
            pd[n_hacks] = a4;
        }
    }
    int p = prime[pcnt - rand() % (pcnt / 10)];
    int a = try_prime(p);
    for (int i = 1; i <= q; ++i) {
        if (mode != SAME) {
            p = rand() % (maxp - 1) + 2;
            a = try_prime(p);            
        }
        if (mode == SAME || mode == PRIME) {
            cout << a << " " << try_prime(p) << " " << p << endl;
        }
        else {
            if (rand() % 5 == 0) {
                int t = rand() % n_hacks + 1;
                int rv = pc[t] * pd[t];

                p = pb[t], a = pa[t];
                cout << a << " " << (long long) rv * (rand() % (p / gcd(rv, p) - 1) + 1) % p << " " << p << endl;
            }
            else {
                int t = rand() % 3;
                if (t == 0)
                    cout << a << " " << try_prime(p) << " " << p << endl;
                else if (t == 1)
                    cout << a << " " << rand() % (p-1) + 1 << " " << p << endl;
                else {
                    cout << a << " " << (rand() % (p / gcd(phi[p], p) - 1) + 1) * gcd(phi[p], p) << " " << p << endl;
		}
            }    
        }
    }

    while (time(NULL) - tn == 0);
    cerr << "fin case." << endl;
}
