#include <cstdio>
#include <algorithm>
#include <ctype.h>
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
const int maxn = 1e6 + 100;
int n, a[maxn], ansx[maxn], ansy[maxn], tot, h;
int x2[maxn], x2num, x1[maxn], y1[maxn], x1num, y1num, used[maxn];
int X[maxn], Y[maxn];
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(a[i]);
    for (int i = n; i; --i)
    {
        if (a[i] == 1) ansx[++tot] = i, ansy[tot] = ++h, x1[++x1num] = tot, y1[++y1num] = tot;
        else if (a[i] == 2)
        {
            while (used[x1[x1num]]) --x1num;
            if (x1num == 0) goto fail;
            ansx[++tot] = i, ansy[tot] = ansy[x1[x1num]], used[x1[x1num--]] = 1, x2[++x2num] = tot, y1[++y1num] = tot;
        }
        else if(a[i] == 3)
        {
            while(used[x2[x2num]]) --x2num;
            if(x2num)
            {
                ansx[++tot] = i,ansy[tot] = ++h;
                ansx[++tot] = ansx[x2[x2num]], used[x2[x2num--]] = 1, ansy[tot] = h;
                x2[++x2num] = tot - 1, y1[++y1num] = tot - 1;
                continue;
            }
            while (used[y1[y1num]]) --y1num;
            if (y1num == 0) goto fail;
            ansx[++tot] = i, ansy[tot] = ++h;
            ansx[++tot] = ansx[y1[y1num]], used[y1[y1num--]] = 1, ansy[tot] = h;
            y1[++y1num] = tot - 1;
        }
    }
    printf("%d\n",tot);
    for (int i = 1; i <= tot; ++i) printf("%d %d\n", h - ansy[i] + 1, ansx[i]);
    //for (int i = 1; i <= tot; ++i) printf("%d %d\n", ansx[i], ansy[i]);
    return 0;
fail:
    puts("-1");
    return 0;
}