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
const int maxk = 210;
int n,k;
long long s[maxn];
long long f[maxk][maxn];
int cut[maxk][maxn];
int out[maxk];
void dfs(int tail,int v)
{
    if(v == 0)
        return;
    out[v] = cut[v][tail];
    dfs(cut[v][tail],v-1);
}
int main()
{
    read(n);
    read(k);
    for(int i = 1;i<=n;++i)
        read(s[i]),s[i] += s[i-1];
    for(int v = 1;v<=k;++v)
    {
        for(int i = v+1;i<=n;++i)
            for(int j = v;j<i;++j)
            {
                if(f[v][i] < f[v-1][j] + (s[i]-s[j]) * s[j])
                    f[v][i] = f[v-1][j] + (s[i] - s[j]) * s[j],cut[v][i] = j;
            }
    }
    printf("%lld\n",f[k][n]);
    dfs(n,k);
    for(int i = 1;i<=k;++i)
        printf("%d ",out[i]);
    return 0;
}