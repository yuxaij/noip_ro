#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "testlib.h"
using namespace std;

char rep[(int) 1e7 + 10];
char res[(int) 1e7 + 10];

int main(int argc, char **argv)  {
  registerGen(argc, argv, 1);
  int len = rnd.next(5, 20); 
  int limit, ksize;
  sscanf(argv[1], "%d", &limit);
  sscanf(argv[2], "%d", &ksize);
  sscanf(argv[3], "%s", rep);
  int t = strlen(rep);
  for (int i = 0; i < limit; ++i)
	res[i] = rep[i % t];
  printf("%d %d\n", limit, ksize);
  printf("%s\n", res);
}