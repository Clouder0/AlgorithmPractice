#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 1e5 + 100;
struct node { int to,next; } E[maxn];
int head[maxn],tot;
inline void addE(const int &x,const int &y) { E[++tot].next = head[x],E[tot].to = y; head[x] = tot;}
int n, a[maxn], H[maxn], cnt,sum[maxn],ans[maxn];
inline int lowbit(int x){return x & -x;}
inline void add(int x,int k){for(;x<=cnt;x+=lowbit(x)) sum[x] += k;}
inline int ask(int x){int res = 0;for(;x>0;x-=lowbit(x)) res += sum[x];return res;}
void dfs(int u)
{
    add(a[u],1);
    int old = ask(cnt) - ask(a[u]);
    for (int p = head[u]; p; p = E[p].next) dfs(E[p].to);
    ans[u] = ask(cnt) - ask(a[u]) - old;
}
int main()
{
    scanf("%d",&n);
    for (int i = 1; i <= n; ++i) scanf("%d",a + i),H[++cnt] = a[i];
    sort(H + 1,H + 1 + cnt),cnt = unique(H + 1,H + 1 + cnt) - H - 1;
    for (int i = 1; i <= n; ++i) a[i] = lower_bound(H + 1,H + 1 + cnt,a[i]) - H;
    for (int i = 2,x; i <= n; ++i) scanf("%d",&x),addE(x,i);
    dfs(1);
    for (int i = 1; i <= n; ++i) printf("%d\n",ans[i]);
    return 0;
}