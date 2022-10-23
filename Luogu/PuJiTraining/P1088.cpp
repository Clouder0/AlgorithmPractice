#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, all[10010];
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", all + i);
    while (m--)
        next_permutation(all + 1, all + 1 + n);
    for (int i = 1; i <= n; ++i)
        printf("%d ", all[i]);
    return 0;
}