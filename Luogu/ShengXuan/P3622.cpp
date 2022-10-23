#include <cstdio>
#include <cstring>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e4 + 10,maxm = 5e4 + 10;
const int magic = 15;
int n,m;
int f[maxn][40],num[maxn][40];
int main()
{
    read(n),read(m);
    for(int i = 1;i<=m;++i)
    {
        int E,F,L,x,fear = 0,like = 0;
        read(E),read(F),read(L);
        for(int j = 1;j<=F;++j)
        {
            read(x);
            fear |= 1 << ((x - E + n) % n);
        }
        for(int j = 1;j<=L;++j)
        {
            read(x);
            like |= 1 << ((x - E + n) % n);
        }
        for(int j = 0;j<32;++j) if((like & j) || (fear & ~j)) ++num[E][j];
    }
    int ans = 0;
    for(int i = 0;i<32;++i)
    {
        std::memset(f[0],128,sizeof(f[0]));
        f[0][i] = 0;
        for(int j = 1;j<=n;++j)
            for(int k = 0;k<32;++k)
                f[j][k] = max(f[j-1][(k&magic)<<1],f[j-1][((k&magic)<<1)|1]) + num[j][k];
        if(ans < f[n][i]) ans = f[n][i];
    }
    printf("%d",ans);
    return 0;
}