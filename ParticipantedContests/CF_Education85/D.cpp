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
int T;
long long n,l,r;
long long s[maxn];
long long f;
int main()
{
    read(T);
    while(T--)
    {
        bool flag = false;
        long long lp = 1,rp = 1;
        long long lp2;
        long long rp2;
        read(n);
        f = n * (n-1) + 1;
        read(l);
        read(r);
        for(int i = 1;i<=n;++i)
            s[i] = ((n-i) << 1) + s[i-1];
        if(l == s[n]+1)
        {
            flag = true;
            goto end;
        }
        if(r == s[n]+1)
        {
            flag = true;
            --r;
        }
        while(s[lp] < l)
            ++lp;
        while(s[rp] < r)
            ++rp;
        lp2 = l - s[lp-1];
        rp2 = r - s[rp-1];
        if(lp == rp)
        {
            for(int i = lp2;i<=rp2;++i)
            {
                if(i & 1)
                    printf("%lld ",lp);
                else
                    printf("%lld ",lp + (i>>1));
            }
            goto end;
        }
        for(long long i = lp2;i<=s[lp] - s[lp-1];++i)
        {
            if(i & 1)
                printf("%lld ",lp);
            else
                printf("%lld ",lp + (i>>1));
        }
        for(long long i = lp+1;i<rp;++i)
        {
            for(long long p = 1;p<=s[i] - s[i-1];++p)
            {
                if(p & 1)
                    printf("%lld ",i);
                else
                    printf("%lld ",i + (p>>1));
            }
        }
        for(long long i = 1;i<=rp2;++i)
        {
            if(i & 1)
                printf("%ld ",rp);
            else
                printf("%lld ",rp + (i >> 1));
        }
        end:
        if(flag)
            printf("1");
        printf("\n");
    }
    return 0;
}