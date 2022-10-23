#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define int long long
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
const int maxn = 1e5 + 100;
int n,L,R;
int a[maxn], l[maxn], r[maxn];
long long minsum,maxsum;
bool check(int num)
{
    long long left = 0;
    for (int i = 1; i <= n; ++i) 
    {
        if (num * l[i] > a[i]) return 0;
        left += std::min(num * (r[i] - l[i]), a[i] - num * l[i]);
    }
    return 1ll * num * (L - minsum) <= left;
}
signed main()
{
    read(n),read(L),read(R);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= n; ++i) read(l[i]), read(r[i]), minsum += l[i],maxsum += r[i];
    if (minsum > R || maxsum < L) { puts("0"); return 0; }
    int ll = 0, rr = 1 << 30, mid, ans = 0;
    while (ll <= rr)
    {
        mid = ll + rr >> 1;
        if (check(mid)) ans = mid, ll = mid + 1;
        else rr = mid - 1;
    }
    printf("%lld\n", ans);
    return 0;
}