#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "testlib.h"
using namespace std;

char s[5000010];

int main(int argc, char **argv)  {
  registerGen(argc, argv, 1);
  int len = rnd.next(4, 10), limit, ksize;
  for (int i = 1; i <= len; ++i)  {
	s[i] = rnd.next(0, 1) + 'a';
  }
  sscanf(argv[1], "%d", &limit);
  sscanf(argv[2], "%d", &ksize);
  while (len <= limit)  {
	int nlen = len;
	for (int j = 1; j <= ksize; ++j)  {
	  for (int k = 1; k <= nlen; ++k)  {
		s[++len] = s[k];
		if (len >= limit)
		  break;
          }
          if (len >= limit)
		  break;
	  }
        if (len >= limit)
		  break;
	int p = rnd.next(0, nlen);
	for (int k = 1; k <= p; ++k)  {
	  s[++len] = s[k];
	  if (len >= limit)
		break;
	}
        if (len >= limit)
		  break;
	int q = rnd.next(0, 3);
	for (int k = 1; k <= q; ++k)  {
	  s[++len] = rnd.next(0, 1) + 'a';
	  if (len >= limit)
		break;
	}
        if (len >= limit)
		  break;
  }
  printf("%d %d\n", len, ksize);
  printf("%s\n", s + 1);
}