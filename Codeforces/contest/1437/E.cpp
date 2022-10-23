#include <cstdio>
#include <algorithm>
#include <ctype.h>
#include <cstring>
using namespace std; 
const int bufSize = 1e6;
#define DEBUG
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
const int maxn = 5e5 + 100;
int n, k, a[maxn], b[maxn], f[maxn], h[maxn], hcnt;
int minn[maxn * 2], vis[maxn * 2], tim;
inline void clear() { ++tim; }
inline void check(int x) { if (vis[x] != tim) minn[x] = 1 << 30, vis[x] = tim; }
inline void add(int x, int k)
{
    for (; x <= hcnt; x += x & -x) check(x), minn[x] = std::min(minn[x], k);
}
inline int ask(int x)
{
    int res = 1 << 30;
    for (; x > 0; x -= x & -x) check(x), res = std::min(res, minn[x]);
    return res;
}
int main()
{
    read(n), read(k);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = 1; i <= k; ++i) read(b[i]);
    memset(f, 0x3f, sizeof(f));
    b[++k] = n + 1, a[n + 1] = 1 << 30;
    f[0] = 0, a[0] = - 1 << 30;
    for (int i = 0; i <= n + 1; ++i) h[++hcnt] = a[i] - i;
    sort(h + 1, h + 1 + hcnt), hcnt = unique(h + 1, h + 1 + hcnt) - h - 1;
    for (int i = 1; i <= k; ++i)
    {
        int l = b[i - 1] + 1, r = b[i] - 1;
        for (int j = l; j <= r; ++j)
        {
            int t = lower_bound(h + 1, h + 1 + hcnt,a[j] - j) - h;
            f[j] = std::min(f[j], ask(t) + j - 1);
            add(t, f[j] - j);
        }
        int t = lower_bound(h + 1, h + 1 + hcnt, a[b[i]] - b[i]) - h;
        f[b[i]] = std::min(f[b[i]], ask(t) + b[i] - 1);
        clear(), add(t, f[b[i]] - b[i]);
    }
    if(f[n + 1] <= n) printf("%d\n",f[n + 1]);
    else puts("-1");
    return 0;
}