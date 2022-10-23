#include <cstdio>
#include <cstring>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 19;
int n,m;
int w[maxn];
int f[(1<<(maxn-1)) + 1000];
int g[(1<<(maxn-1)) + 1000];
void dfs(int status)
{
    if(f[status] != -1)
        return;
    if(!status)
    {
        f[status] = 0;
        g[status] = m;
        return;
    }
    int mint = 1<<30,ming = 1<<30,minw = 0;
    for(int i = 1;i<=n;++i)
        if(status & (1<<(i-1)))
        {
            int v = status ^ (1<<(i-1));
            dfs(v);
            if(f[v] < mint)
                mint = f[v],ming = g[v] + w[i],minw = w[i];
            else if(f[v] == mint && g[v] + w[i] < ming)
                ming = g[v] + w[i],minw = w[i];
        }
    if(ming > m)
    {
        f[status] = mint + 1;
        g[status] = minw;
    }
    else
        f[status] = mint,g[status] = ming;
}
int main()
{
    read(n);
    read(m);
    for(int i = 1;i<=n;++i)
        read(w[i]);
    for(int i = 0;i<(1<<n);++i)
        f[i] = -1;
    dfs((1<<n)-1);
    printf("%d",f[(1<<n)-1]);
    return 0;
}