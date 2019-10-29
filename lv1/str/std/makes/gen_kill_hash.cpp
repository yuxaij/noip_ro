#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include "testlib.h"
using namespace std;

char s[5000010];
char res[5000010];
char sx[100010];
char sy[100010];

int main(int argc, char **argv)  {
  registerGen(argc, argv, 1);
  int mode, id = 0;
  sscanf(argv[1], "%d", &mode);
  if (mode == 1)  {
	char a = rnd.next('a', 'z');
	char b = rnd.next('a', 'z');
	int n = 100738, k = 10;
	for (int i = 1; i <= 1000; ++i)  {
	  s[i] = i <= 500 ? a : b;
	}
	for (int i = 1; i <= 10; ++i)
	  for (int j = 1; j <= 1000; ++j)  {
		res[++id] = s[j];
	  }
	for (int i = 1; i <= 500; ++i)  {
	  res[++id] = i == 101 ? b : a;
	}
	for (int i = 1; i <= 500; ++i)
	  res[++id] = b;
	while (id < n)  {
	  for (int j = 1; j <= 1000; ++j)  {
		res[++id] = s[j];
	  }
	}
	printf("%d %d\n", id, k);
	printf("%s\n", res + 1);
  }
  if (mode == 2)  {
	char a = rnd.next('a', 'z');
	char b = rnd.next('a', 'z');
	int n = 1000000, k = 10, t = 1;
	s[1] = a;
	for (int i = 0; i < 11; ++i)  {
	  for (int j = 1; j <= (1 << i); ++j)
		s[++t] = s[j] == a ? b : a;
	}
	for (int i = t + 1; i <= 4000; ++i)  {
	  s[++t] = a;
	}
	for (int i = t + 1; i <= 5000; ++i)  {
	  s[++t] = b; 
	}
	for (int i = 1; i <= k; ++i)  {
	  for (int j = 1; j <= t; ++j)
		res[++id] = s[j];
	}
	for (int i = 1; i <= t; ++i)  {
	  if (i <= 2048)
		res[++id] = s[i] == a ? b : a;
	  else
		res[++id] = s[i];
	}
	while (id < n)  {
	  for (int i = 1; i <= t; ++i)
		res[++id] = s[i]; 
	}
	printf("%d %d\n", id, k);
	printf("%s\n", res + 1);
  }
  if (mode == 3)  {
	char a = rnd.next('a', 'z');
	char b = rnd.next('a', 'z');
	int n = 900000, k = 10, t = 1;
	sx[1] = a;
	for (int i = 0; i < 11; ++i)  {
	  for (int j = 1; j <= (1 << i); ++j)
		sx[++t] = sx[j] == a ? b : a;
	}
	for (int i = t + 1; i <= 7000; ++i)  {
	  sx[++t] = a;
	}
	for (int i = t + 1; i <= 2000; ++i)  {
	  sx[++t] = b; 
	}
	for (int i = 1; i <= 2000; ++i)  {
	  sy[i] = a;
	}
        sy[2001] = 0;
	sprintf(s + 1, "%s%s", sy + 1, sx + 1);
	t = strlen(s + 1);
	for (int i = 1; i <= k; ++i)  {
	  for (int j = 1; j <= t; ++j)
		res[++id] = s[j];
	}
	for (int i = 1; i <= t; ++i)  {
	  if (i >= 2001  &&  i <= 4048)
		res[++id] = s[i] == a ? b : a;
	  else
		res[++id] = s[i];
	}
	while (id < n)  {
	  for (int i = 1; i <= t; ++i)
		res[++id] = s[i]; 
	}
	printf("%d %d\n", id, k);
	printf("%s\n", res + 1);
  }
}