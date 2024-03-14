#include <cstdio>
#include <algorithm>
#include <vector>

const int maxn = 6e5 + 100;

struct node
{
    int to, next;
} E[maxn];
int head[maxn], cnt;
const void add(int u, int v) { E[++cnt].next = head[u], head[u] = cnt, E[cnt].to = v; }
int n, m, fa[maxn],dep[maxn];
long long sum[maxn];
void ins(int x, int val)
{
    for (; x > 0; x -= x & -x) sum[x] += val;
}
long long ask(int x)
{
    long long res = 0;
    for (; x <= 2 * n; x += x & -x) res += sum[x];
    return res;
}
std::vector<std::pair<int, int>> V[maxn];
long long ans[maxn];
void dfs(int u) {
    for(auto p : V[u]) {
        int d = p.first, x = p.second;
        ins(dep[u] + std::min(d, n), x);
    }
    ans[u] = ask(dep[u]);
    for(int p = head[u];p;p=E[p].next) {
        int v = E[p].to;
        if(v == fa[u]) continue;
        dep[v] = dep[u] + 1,fa[v] = u;
        dfs(v);
    }
    for(auto p : V[u]) {
        int d = p.first, x = p.second;
        ins(dep[u] + std::min(d, n), -x);
    }
}
int main()
{
    scanf("%d", &n);
    for (int i = 1, a, b; i < n; ++i) scanf("%d%d", &a, &b), add(a, b), add(b, a);
    scanf("%d", &m);
    while (m--)
    {
        int v, d, x;
        scanf("%d%d%d", &v, &d, &x);
        V[v].push_back(std::make_pair(d, x));
    }
    dep[1] = 1,dfs(1);
    for (int i = 1; i <= n; ++i) printf("%lld ",ans[i]);
    return 0;
}