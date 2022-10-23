#include <cstdio>
const int maxn = 1e5 + 10;
int n, m, fa[maxn];
inline int find(int x)
{
    return fa[x] == x ? x : find(fa[x]);
}
inline void unite(int a, int b)
{
    a = find(a), b = find(b);
    fa[b] = a;
}
int main()
{
    scanf("%d%d", &n,&m);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1; i <= m; ++i) 
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if (a == 1)
            unite(b, c);
        else
            puts(find(b) == find(c) ? "Y" : "N");
    }
    return 0;
}