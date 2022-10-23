#include <cstdio>
template<typename T>
inline T abs(const T &x){return x<0?-x:x;}
template<typename T>
inline T min(const T &a,const T &b){return a<b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e4 + 10;
int n;
int l[maxn],r[maxn];
int f[maxn][2];
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(l[i]), read(r[i]);
    f[1][0] = r[1] + r[1] - l[1] - 1;
    f[1][1] = r[1] - 1;
    for (int i = 2; i <= n + 1; ++i)
    {
        f[i][0] = min(f[i - 1][0] + abs(r[i] - l[i - 1]) + r[i] - l[i] + 1, f[i - 1][1] + abs(r[i] - r[i - 1]) + r[i] - l[i] + 1);
        f[i][1] = min(f[i - 1][0] + abs(l[i] - l[i - 1]) + r[i] - l[i] + 1, f[i - 1][1] + abs(l[i] - r[i - 1]) + r[i] - l[i] + 1);
    }
    printf("%d", min(f[n][0] + n - l[n], f[n][1] + n - r[n]));
    return 0;
}