#include <cstdio>
using namespace std;
inline char nc()
{
    static char buf[100000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c; static int flag;flag = 1,r=0;
    for(c=nc();c>'9'||c<'0';c=nc()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc()); r *= flag;
}
int primes[100000],cnt;
int sum[1000010];
bool notprime[1000010];
int n,m;
void init()
{
    notprime[1] = true;
    for(int i = 2;i<=m;++i)
    {
        if(!notprime[i])
            primes[++cnt] = i;
        for(int j = 1;primes[j] * i <= m && j <= cnt;++j)
        {
            notprime[primes[j] * i] = true;
            if(!(i % primes[j]))
                break;
        }
        sum[i] = cnt;
    }
}
int main()
{
    read(n);
    read(m);
    init();
    int l,r;
    for(;n;--n)
    {
        read(l);
        read(r);
        if(l < 1 || l > m || r < 1 || r > m)
            printf("Crossing the line\n");
        else
            printf("%d\n",sum[r] - sum[l-1]);
    }
    return 0;
}