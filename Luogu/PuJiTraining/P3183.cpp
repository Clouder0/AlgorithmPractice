#include <cstdio>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 10;
const int maxm = 2e5 + 10;
struct node
{
    int to,next;
}E[maxm];
int head[maxn],in[maxn],out[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].to = y;
    E[tot].next = head[x];
    head[x] = tot;
}
int n,m;
int f[maxn];
int dfs(int u)
{
    if(f[u])
        return f[u];
    if(!out[u])
        return f[u] = 1;
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        f[u] += dfs(v);
    }
    return f[u];
}
int main()
{
    read(n);
    read(m);
    int x,y;
    for(int i = 1;i<=m;++i)
    {
        read(x);
        read(y);
        add(x,y);
        in[y]++,out[x]++;
    }
    int ans = 0;
    for(int i = 1;i<=n;++i)
        if(in[i] == 0 && out[i] != 0)
            ans += dfs(i);
    printf("%d",ans);
    return 0;
}