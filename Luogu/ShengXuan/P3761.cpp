#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 5100;
struct node
{
    int to,next,val;
}E[maxn << 1];
int head[maxn],tot;
inline void add(int x,int y,int val)
{
    E[++tot].to = y,E[tot].next = head[x],head[x] = tot,E[tot].val = val;
}
int n, A[maxn], B[maxn],C[maxn];
int maxx[maxn], secx[maxn], maxson[maxn];
void dfs(int u, int fa,int &maxdia)
{
    maxx[u] = secx[u] = maxson[u] = 0;
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if (v == fa) continue;
        dfs(v, u,maxdia);
        if (maxx[v] + E[p].val > maxx[u]) secx[u] = maxx[u], maxx[u] = maxx[v] + E[p].val, maxson[u] = v;
        else if (maxx[v] + E[p].val > secx[u]) secx[u] = maxx[v] + E[p].val;
    }
    maxdia = max(maxdia,maxx[u] + secx[u]);
}
void dfs2(int u,int fa,int &minn)
{
    for (int p = head[u]; p; p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        int t = (maxson[u] != v ? maxx[u] : secx[u]) + E[p].val;
        if (t > maxx[v]) secx[v] = maxx[v], maxx[v] = t, maxson[v] = u;
        else if(t > secx[v]) secx[v] = t;
        dfs2(v,u,minn);
    }
    minn = min(minn,maxx[u]);
}
bool tag[maxn];
int main()
{
    scanf("%d", &n);
    for (int i = 1, a, b, c; i < n; ++i) scanf("%d %d %d", &a, &b, &c), add(a, b, c), add(b, a, c), A[i] = a, B[i] = b, C[i] = c;
    int ans = 1 << 30;
    int maxdia = 0;
    dfs(1, 0, maxdia);
    for (int i = 1; i < n; ++i)
        if ((maxx[A[i]] + secx[A[i]] == maxdia) || (maxx[B[i]] + secx[B[i]] == maxdia)) tag[i] = 1;
    for (int i = 1; i < n; ++i)
    {
        if(!tag[i]) continue;
        int maxa = 0, maxb = 0;
        dfs(A[i], B[i], maxa), dfs(B[i], A[i], maxb);
        int mina = maxx[A[i]], minb = maxx[B[i]];
        dfs2(A[i], B[i], mina), dfs2(B[i], A[i], minb);
        ans = min(ans, max(max(maxa, maxb), mina + minb + C[i]));
    }
    printf("%d\n",ans);
    return 0;
}