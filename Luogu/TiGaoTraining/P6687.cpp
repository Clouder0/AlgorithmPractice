#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 2e6 + 100;
int n;
int a[2][maxn],b[2][maxn];
int vis1[maxn],vis2[maxn],id[maxn];
struct Bit
{
    int sum[maxn];
    inline int lowbit(const int &x){return x & -x;}
    inline void add(int x,int k){ for (; x <= n; x += lowbit(x)) sum[x] += k;}
    inline int ask(int x)
    {
        int res = 0;
        for (; x > 0; x -= lowbit(x)) res += sum[x];
        return res;
    }
}A;
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[0][i]);
    for (int i = 1; i <= n; ++i) read(a[1][i]);
    for (int i = 1; i <= n; ++i) read(b[0][i]);
    for (int i = 1; i <= n; ++i) read(b[1][i]);
    for (int i = 2; i <= n; i += 2) std::swap(a[0][i],a[1][i]),std::swap(b[0][i],b[1][i]);
    for(int i = 1;i<=n;++i) vis1[b[0][i]] = vis2[b[1][i]] = i;
    for (int i = 1; i <= n; ++i) 
    {
        if(!(vis1[a[0][i]] | vis2[a[1][i]]) || vis1[a[0][i]] != vis2[a[1][i]])
        {
            puts("dldsgay!!1");
            return 0;
        }
    }
    for (int i = 1; i <= n; ++i) id[i] = vis1[a[0][i]];
    long long ans = 0;
    for (int i = 1; i <= n; ++i) 
    {
        A.add(id[i],1);
        ans += i - A.ask(id[i]);
    }
    printf("%lld\n",ans);
    return 0;
}