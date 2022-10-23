#include <cstdio>
const int mod = 10000007;
const int mod2 = 11405147;
const int maxn = 110;
const int bufSize = 1000000;
inline char nc()
{
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=nc();c>'9'||c<'0';c=nc()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r*10+(c^48)),r = r>mod?r%mod:r,c=nc());
    if(flag == -1) r = -r + mod;
}
int n,m;
long long a[maxn],x[maxn];
int res[1000000],tot;
int main()
{
    read(n);
    read(m);
    for(int i = 0;i<=n;++i)
        read(a[i]);
    for(int i = 1;i<=m;++i)
    {
        x[0] = 1;
        for(int j = 1;j<=n;++j)
        {
            x[j] = x[j-1] * i;
            if(x[j] > mod) x[j] %= mod;
        }
        long long ans = 0;
        for(int j = 0;j<=n;++j)
        {
            ans = ans + a[j] * x[j];
            if(ans >= mod)
                ans %= mod;
        }
        if(ans == 0)
            res[++tot] = i;
    }
    printf("%d\n",tot);
    for(int i = 1;i<=tot;++i)
        printf("%d\n",res[i]);
    return 0;
}