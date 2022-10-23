#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int maxn = 1e5 + 100;
int n, a[maxn], b[maxn], fa[maxn];
inline void update(int x, int k) { for (; x <= n; x += x & -x) a[x] = std::max(a[x], k); }
inline int ask(int x)
{
    int res = 0;
    for (; x > 0; x -= x & -x) res = std::max(res, a[x]);
    return res;
}
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n + 1; ++i) fa[i] = i;
    int num = 0;
    for (int i = 1, x; i <= 2 * n; ++i)
    {
        char opt[2];
        scanf("%s",opt);
        if (opt[0] == '+') ++num;
        else
        {
            scanf("%d", &x);
            int id = find(ask(n - x + 1) + 1);
            if (id <= num) b[id] = x, update(n - x + 1, num), fa[id] = find(id + 1);
            else { puts("NO"); return 0; }
        }
    }
    puts("YES");
    for (int i = 1; i <= n; ++i) printf("%d ", b[i]);
    return 0;
}