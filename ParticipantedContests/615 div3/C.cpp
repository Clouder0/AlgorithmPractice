#include <cstdio>
#include <cmath>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int t,n;
bool notprime[50000000];
int primes[10000000],cnt;
inline void getprime(int x)
{
    notprime[1] = true;
    for(int i = 2;i<=x;++i)
    {
        if(!notprime[i])
            primes[++cnt] = i;
        for(int j = 1;j<=cnt && primes[j] * i <= x;++j)
        {
            notprime[i*primes[j]] = true;
            if(i % primes[j] == 0)
                break;
        }
    }
}
int main()
{
    read(t);
    getprime(49000000);
    while(t--)
    {
        read(n);
        int sq = sqrt(n);
        for(int i = sq;i>=2;--i)
        {
            if(n % i)
                continue;
            int a = i,b = n/i;
            if(!notprime[a] && !notprime[b])
                continue;
            if(a == b)
                continue;
            int p,q;
            if(notprime[a])
                p = a,q = b;
            else if(notprime[b])
                p = b,q = a;
            for(int j = 2;j*j<p;++j)
            {
                if(p % j || p / j == q || j == q)
                    continue;
                puts("YES");
                printf("%d %d %d\n",j,p / j,q);
                goto end;
            }
        }
        puts("NO");
        end:;
    }
    return 0;
}