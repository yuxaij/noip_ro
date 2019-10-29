#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const int MAXP = int(1e7);
using namespace std;

int prime[MAXP + 10];
int phi[MAXP + 10];
int fr[MAXP + 10];
int pcnt;

int prs[110], times[110], cnt;
int prs_phi[110], times_phi[110], cnt_phi; 

int pa[MAXP + 10], pb[MAXP + 10], pc[MAXP + 10];
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
int try_to_find(int power, int p, int a) {
    int rs = min(10000, p);
    for (int i = 2; i < rs; ++i)
        if (fpm(i, power, p) == 1)
            if (a == power || (fpm(i, a, p) != 1 && fpm(i, power / a, p) != 1))
                return i;
    return -1;
}
int main(int argc, char **argv) {
    //int p, q, mode;
    //sscanf(argv[1], "%d", &q);
    //sscanf(argv[2], "%d", &p);
    //sscanf(argv[3], "%d", &mode);

    phi[1] = 0;
    for (int i = 2; i <= MAXP; ++i) {
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
    for (int i = 2; i <= MAXP; i += rand() % 20 + 1) {
        int p = i;

        get_primes(p, prs, times, cnt);
        get_primes(phi[p], prs_phi, times_phi, cnt_phi);

        if (cnt == 1)
            continue;

        for (int j = 1; j <= cnt_phi; ++j) {
            int r = 0;
            while (p % prs_phi[j] == 0)
                ++r, p /= prs_phi[j];

            if (r > times_phi[j]) { 
                int prsp = 1;
                for (int k = 1; k <= times_phi[j]; ++k)
                    prsp *= prs_phi[j];
                bool is_1 = cnt_phi == 1;

                if (is_1)
                    continue;
                int rdt = is_1 ? 1 : rand() % (cnt_phi - 1) + 1;
                int rdp = prsp * (is_1 ? 1 : prs_phi[rdt < j ? rdt : rdt + 1]);

                if (rdp * prs_phi[j] == i)
                    continue;
                int v = try_to_find(rdp, i, prsp);
                if (v != -1) {
                    ++pt;
                    //pa[++pt] = v, pb[pt] = p, pc[pt] = prime[j];
                    cout << pt << " " << v << " " << i << " " << prsp << " " << prs_phi[j] << endl; 
                    cerr << pt << " " << v << " " << i << " " << prsp << " " << prs_phi[j] << endl; 
                }
            }
        }
    }
}
