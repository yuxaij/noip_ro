#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "testlib.h"
using namespace std;

char s[(int) 1e7 + 10];
char res[(int) 1e7 + 10];

int main(int argc, char **argv)  {
  registerGen(argc, argv, 1);
  int len = rnd.next(5, 20); 
  for (int i = 1; i <= len; ++i)  {
	s[i] = rnd.next(0, 1) + 'a';
  }
  int limit, ksize;
  sscanf(argv[1], "%d", &limit);
  sscanf(argv[2], "%d", &ksize);
  int times = limit / len, id = 0;
  for (int i = 1; i <= times; ++i)  {
	for (int j = 1; j <= len; ++j)
	  res[id++] = s[j];
  }
  printf("%d %d\n", id, ksize);
  printf("%s\n", res);
}