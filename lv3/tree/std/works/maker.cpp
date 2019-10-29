#include <ctime>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "maker_draw.cpp"
using namespace std;

int dst(int x) {
    return max((1 - (0.05 * rand() / (~0U>>1))) * x, 1.);
}
int main(int argc, char **argv) {
    srand((unsigned)time(NULL));
    int n = int(1e5), m1 = n, m2 = n;   
    /*
    gen_data("test.in", SINGLE_PATH_GEN, dst(n), dst(2000), true, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 20, 
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    */

    gen_data("1.in", PATH_GEN, dst(300), dst(30), true, 100, 100, 100 * 3, int(1), int(100), 20,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    gen_data("2.in", PATH_GEN, dst(600), dst(100), true, 300, 300, 300 * 4, int(1), int(1000), 20,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    gen_data("3.in", PATH_GEN, dst(1000), dst(200), true, 500, 500, 500 * 5, int(1), int(1e5), 20,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);

    gen_data("4.in", SINGLE_PATH_GEN, dst(n), dst(2000), true, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 20, 
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    gen_data("5.in", SINGLE_PATH_GEN, dst(n), dst(5000), true, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 20,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    gen_data("6.in", SINGLE_PATH_GEN, dst(n), dst(20000), true, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 20,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    gen_data("7.in", SINGLE_PATH_GEN, dst(n), dst(10000), true, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 20,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    gen_data("8.in", SINGLE_PATH_GEN, dst(n), dst(20000), false, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 20,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    gen_data("9.in", SINGLE_PATH_GEN, dst(n), dst(10000), false, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 20,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);

    gen_data("10.in", PATH_GEN, dst(n), dst(2000), true, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 0, 
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    gen_data("11.in", PATH_GEN, dst(n), dst(5000), true, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 0,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    gen_data("12.in", PATH_GEN, dst(n), dst(20000), true, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 0,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    gen_data("13.in", PATH_GEN, dst(n), dst(10000), true, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 0,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    gen_data("14.in", PATH_GEN, dst(n), dst(20000), false, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 0,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    gen_data("15.in", PATH_GEN, dst(n), dst(10000), false, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 0,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);

    gen_data("17.in", PATH_GEN, dst(n), dst(5000), true, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 20,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    gen_data("18.in", PATH_GEN, dst(n), dst(20000), true, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 20,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    gen_data("19.in", PATH_GEN, dst(n), dst(10000), true, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 20,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    gen_data("20.in", PATH_GEN, dst(n), dst(20000), false, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 20,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
    gen_data("16.in", PATH_GEN, dst(n), dst(10000), false, dst(m1), dst(m2), m1 * 5, int(1), int(1e5), 20,
        n_parts[1], sizes[1], powes[1], n_parts[0], sizes[0], powes[0]);
}
