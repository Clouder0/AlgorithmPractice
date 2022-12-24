#include <cstdio>
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
    putchar('A' + i);
  return 0;
}