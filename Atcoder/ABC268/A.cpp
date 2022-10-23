#include <cstdio>
#include <algorithm>
int a[5];
int main()
{
    for (int i = 0; i < 5; ++i) scanf("%d", a + i);
    std::sort(a, a + 5);
    printf("%d\n", int(std::unique(a, a + 5) - a));
    return 0;
}