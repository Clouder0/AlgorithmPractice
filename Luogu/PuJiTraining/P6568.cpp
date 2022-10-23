#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e6 + 100;
int sum[maxn];
int n,k;
int main()
{
    read(n),read(k);
    for(int i = 1;i<=n;++i)
        read(sum[i]),sum[i] += sum[i-1];
    int ans = 0;
    for(int i = k+1;i<=n;++i)
        if(sum[i] - sum[i-k-1] > ans)
            ans = sum[i] - sum[i-k-1];
    printf("%d",ans);
    return 0;
}