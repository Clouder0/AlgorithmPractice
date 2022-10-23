#include <algorithm>
#include <cstdio>
#include <ctype.h>
const int maxn = 1e6 + 100;
int n, m, p, q, c[maxn], to[maxn];
int find(int x) { return to[x] == x ? x : to[x] = find(to[x]); }
int main()
{
    scanf("%d %d %d %d", &n, &m, &p, &q);
    for (int i = 1; i <= n + 1; ++i) to[i] = i;
    for (int i = m; i; --i)
    {
        int l = (1ll * i * p + q) % n + 1;
        int r = (1ll * i * q + p) % n + 1;
        if (l > r) std::swap(l, r);
        for (int j = find(l); j <= r; j = find(j)) c[j] = i, to[j] = j + 1;
    }
    for (int i = 1; i <= n; ++i) printf("%d\n", c[i]);
    return 0;
}