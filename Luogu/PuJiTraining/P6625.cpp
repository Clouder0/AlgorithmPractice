#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
const int maxn = 1e5 + 100;
int n;
long long s[maxn];
int main()
{
    read(n);
    for(int i = 1;i<=n;++i) read(s[i]),s[i] += s[i-1];
    long long ans = 0;
    for(int i = 2;i<=n;++i) if(s[i] > 0) ans += s[i];
    printf("%lld",ans);
    return 0;
}