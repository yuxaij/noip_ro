#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "testlib.h"
using namespace std;

int limit, ksize;
char res[5000010], s[50];

int main(int argc, char **argv)  {
  registerGen(argc, argv, 1);
  sscanf(argv[1], "%d", &limit);
  sscanf(argv[2], "%d", &ksize);
  int id = 0, p = rnd.next(0, 25) + 'a';
  for (int i = 1; i <= limit - 10000; ++i)  {
      res[id++] = p;
  }
  for (int i = 1; i <= 10000; ++i)  {
      res[id++] = rnd.next(0, 25) + 'a';
  }
  printf("%d %d\n", id, ksize);
  printf("%s\n", res);
}