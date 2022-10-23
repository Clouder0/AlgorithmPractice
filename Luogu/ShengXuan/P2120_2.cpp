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
const int maxn = 1e6 + 100;
int n, dis[maxn], num[maxn], cost[maxn];
int q[maxn], qt, qh;
long long S[maxn], T[maxn], f[maxn];
inline long long getx(int x) { return S[x]; }
inline long long gety(int x) { return f[x] + T[x]; }
inline bool cmp(int a, int b, int c) { return (gety(b) - gety(a)) * (getx(c) - getx(b)) > (gety(c) - gety(b)) * (getx(b) - getx(a)); }
inline bool cmp2(int a, int b, long long k)
{
    return gety(b) - gety(a) < k * (getx(b) - getx(a));
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(dis[i]),read(num[i]),read(cost[i]);
    for (int i = 1; i <= n; ++i) S[i] = num[i] + S[i - 1], T[i] = 1ll * num[i] * dis[i] + T[i - 1];
    for (int i = 1; i <= n; ++i)
    {
        f[i] = 1ll << 60;
        for (int j = 0; j < i; ++j)
            f[i] = std::min(f[i], cost[i] + dis[i] * S[i - 1]  - T[i - 1] + f[j] + T[j] - dis[i] * S[j]);
    }
//    for(int i = 1;i<=n;++i) printf("%d %lld\n",i,f[i]);
    printf("%lld\n", f[n]);
    return 0;
}