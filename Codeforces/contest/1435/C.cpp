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
const int maxn = 1e5 + 100;
int n, a[10], b[maxn],tot;
struct node
{
    int val, bid, aid;
} c[maxn * 10];
bool cmp(const node& a, const node& b) { return a.val < b.val; }
int main()
{
    read(a[1]), read(a[2]), read(a[3]), read(a[4]), read(a[5]), read(a[6]);
    read(n);
    for (int i = 1; i <= n; ++i) read(b[i]);
    std::sort(a + 1, a + 7);
    int maxx = -(1 << 30);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= 6; ++j) c[++tot].val = b[i] - a[j], c[tot].bid = i, c[tot].aid = j;
        maxx = std::max(maxx, b[i] - a[6]);
    }
    std::sort(c + 1, c + 1 + tot, cmp);
    for (int i = 1; i <= tot; ++i) printf("%d %d %d\n",c[i].val,c[i].aid,c[i].bid);
    int res = 1 << 30;
    for (int i = 1; i <= tot; ++i)
    {
        int r = i;
        while (r < tot && c[r + 1].val == c[r].val) ++r;
        res = std::min(res,maxx - c[i].val);
        for (int j = i; j <= r; ++j)
            if (c[j].aid == 1) goto end;
            else maxx = std::max(maxx, b[c[j].bid] - a[c[j].aid - 1]);
        i = r;
    }
    end:
    printf("%d\n",res);
    return 0;
}