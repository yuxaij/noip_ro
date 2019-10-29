#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
const int MAXP = int(1e7);
using namespace std;

int prime[MAXP + 10];
int phi[MAXP + 10];
int fr[MAXP + 10];
int cnt;

int gcd(int a, int b) {
    int t;
    while (a)
        t = a, a = b % a, b = t; 
    return b;
}
int ex(int a, int p, int b) {
    if (a == 0)
        return b == 0 ? 0 : -1; 
    int t = ex(p % a, a, (-b % a + a) % a);
    return t == -1 ? t : ((long long) p * t + b) / a;
}
int fpm(int a, int b, int p) {
    long long r = 1;
    for (; b; b >>= 1, a = (long long) a * a % p)
        if (b & 1)
            r = r * a % p;
    return r;
}

int main() {
    phi[1] = 0;
    for (int i = 2; i <= MAXP; ++i) {
        if (prime[i] != -1)
            prime[++cnt] = i, phi[i] = i - 1, fr[i] = 1; 
        for (int j = 1; j <= cnt; ++j) {
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

    int a, b, p;
    while (scanf("%d %d %d", &a, &b, &p) != EOF) {
        int t = gcd(a, p);
        if (t != 1)
            cout << -1 << endl;
        else {
            long long c = phi[p];
            long long t = gcd(b, p);
            c = c / gcd(t, c) * t;

            if (c >= p)
                cout << -1 << endl;
            else {
                int d = gcd(b, p);
                int s = phi[p] / gcd(phi[p], d) * d;
                if (s >= p)
                    cout << -1 << endl;
                else
                    cout << ex(b, p, s) << endl;
            }
        }
    }
}
