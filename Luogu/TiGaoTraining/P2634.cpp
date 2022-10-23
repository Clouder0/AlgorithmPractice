#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e4 + 100;
struct node
{
    int to,next,val;
}E[maxn<<1];
int head[maxn],tot;
inline void add(const int &x,const int &y,const int &val)
{
    E[++tot].next = head[x],E[tot].to = y,E[tot].val = val,head[x] = tot;
}
int n,ans;
int f[maxn][3];
void dfs(int u,int fa)
{
    f[u][0] = 1;
    for(int p = head[u];p;p = E[p].next)
    {
        int v = E[p].to;
        if(v == fa) continue;
        dfs(v,u);
        for(int i = 0;i<3;++i)
            ans += f[u][i] * f[v][((3 - (i + E[p].val) % 3) + 3) % 3] * 2;
        for(int i = 0;i<3;++i)
            f[u][((i+E[p].val) % 3 + 3) % 3] += f[v][i];
    }
}
int gcd(int a,int b)
{
    return b==0?a:gcd(b,a%b);
}
int main()
{
    read(n);
    for(int i = 1;i<n;++i)
    {
        int a,b,c;
        read(a),read(b),read(c);
        add(a,b,c),add(b,a,c);
    }
    ans = n;
    dfs(1,0);
    int g = gcd(ans,n*n);
    printf("%d/%d",ans/g,n*n/g);
    return 0;
}