#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 510;
#define int long long
int n, m, a[maxn], v[maxn][maxn];
int fastpow(int x, int k)
{
    int res = 1;
    while (k)
    {
        if (k & 1) res = res * x % m;
        x = x * x % m;
        k >>= 1;
    }
    return res;
}
struct node
{
    int u,v,val;
}E[maxn * maxn];
int cnt;
bool cmp(const node &a,const node &b){return a.val > b.val;}
int fa[maxn];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void unite(int a, int b) { fa[find(a)] = find(b); }
signed main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%lld", a + i);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < i; ++j) E[++cnt] = {i, j, (fastpow(a[i], a[j]) + fastpow(a[j], a[i])) % m};
    long long res = 0;
    sort(E + 1, E + 1 + cnt, cmp);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1; i <= cnt; ++i)
        if (find(E[i].u) != find(E[i].v)) res += E[i].val, unite(E[i].u, E[i].v);
    printf("%lld\n", res);
    return 0;
}