#include <algorithm>
#include <cstdio>
const int maxn = 1e6 + 100;
struct node
{
    int to,next;
}E[maxn<<1];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot].next = head[x];
    E[tot].to = y;
    head[x] = tot;
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n;
int w[maxn],num[maxn];
int size[maxn],cnt[maxn];
long long f1[maxn],f2[maxn];
int pnum[maxn],ppos[maxn];
void dfs(int u,int fa)
{
    int k = cnt[w[u]];
    size[u] = 1;
    int v,flag = 0,pp = 0;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(v == fa)
            continue;
        int t = cnt[w[u]];
        dfs(v,u);
        f1[u] += (long long)size[u] * size[v];
        size[u] += size[v];
        if(t != cnt[w[u]])
            ++flag,pp = v;
    }
    f1[u] += (long long)size[u] * (n - size[u]);
    if(k || cnt[w[u]] != num[w[u]] - 1)
        ++flag;
    ++cnt[w[u]];
    if(flag == 1)
    {
        if(!pnum[w[u]])
            ppos[w[u]] = u;
        else
        {
            int t = pp ? n - size[pp] : size[u];
            f2[w[u]] = (long long)size[ppos[w[u]]] * t;
        }
        pnum[w[u]]++;
    }
}
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(w[i]),num[w[i]]++,ppos[w[i]] = i;
    int a,b;
    for(int i = 1;i<n;++i)
    {
        read(a);
        read(b);
        add(a,b);
        add(b,a);
    }
    dfs(1,0);
    for(int i = 1;i<=n;++i)
    {
        if(num[i] == 0)
            printf("%lld\n",(long long)n*(n-1)>>1);
        else if(num[i] == 1)
            printf("%lld\n",f1[ppos[i]]);
        else if(pnum[i] == 2)
            printf("%lld\n",f2[i]);
        else
            puts("0");
    }
    return 0;
}