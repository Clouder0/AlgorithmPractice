#include <algorithm>
#include <cstdio>
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
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc())
        if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 4e5 + 100;
int T, n, k, l;
int d[maxn];
int s[maxn], num;
inline int getx(int x)
{
    if (x <= k) return x;
    else return 2 * k - x;
}
inline int getok(int x)
{
    return l - x;  //getx(t) <= l - x is ok.
}
int main()
{
    read(T);
    while (T--)
    {
        read(n), read(k), read(l);
        for (int i = 1; i <= n; ++i) read(d[i]);
        num = 0;
        s[++num] = 0;
        int pos = 0, t = 0;
        for (int i = 1; i <= n; ++i) if (d[i] + k <= l) s[++num] = i;
        for (int i = 1; i <= n; ++i) if (d[i] > l) goto fail;
        if (s[num] != n) s[++num] = n;  //no matter when we get to the n,we can straightly swim to the island.
        for (int i = 1; i < num; ++i)
        {
            pos = s[i] + 1, t = 2 * k - getok(d[s[i] + 1]);
            while (pos < s[i + 1])
            {
                t %= 2 * k;
                int ok = getok(d[pos + 1]);
                if (t < k)
                {
                    if (ok >= getx(t + 1)) ++t, ++pos;
                    else goto fail;
                }
                else
                {
                    if (ok >= getx(t + 1)) ++t, ++pos;
                    else t = 2 * k - ok, ++pos;
                }
            }
        }
        puts("Yes");
        continue;
    fail:
        puts("No");
    }
    return 0;
}