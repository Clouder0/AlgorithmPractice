#include <algorithm>
#include <cstdio>
const int maxn = 1e3 + 100, maxm = 1e4 + 100;
struct edge
{
    int u, v, w;
} E[maxm];
int n, m, k, fa[maxn];
bool cmp(const edge& a, const edge& b) { return a.w < b.w; }
inline int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
inline void unite(int a, int b) { fa[find(a)] = find(b); }
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; ++i) scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].w);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    std::sort(E + 1, E + 1 + m, cmp);
    int cnt = n, sum = 0;
    for (int i = 1; i <= m && cnt > k; ++i)
        if (find(E[i].u) != find(E[i].v)) --cnt, unite(E[i].u, E[i].v), sum += E[i].w;
    if (cnt == k) printf("%d\n", sum);
    else puts("No Answer");
    return 0;
}