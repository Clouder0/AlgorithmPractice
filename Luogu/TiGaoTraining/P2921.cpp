#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
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
int n, to[maxn], bel[maxn], before[maxn], size[maxn], incyc[maxn];
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(to[i]);
    for (int k = 1; k <= n; ++k)
    {
        for (int u = k, pre = 0;; u = to[u], ++pre)
        {
            if (!bel[u]) bel[u] = k, before[u] = pre;
            else if(bel[u] == k)
            {
                size[k] = pre - before[u], incyc[k] = before[u];
                printf("%d\n",pre);
                break;
            }
            else
            {
                size[k] = size[bel[u]];
                incyc[k] = pre;
                printf("%d\n",pre + size[k]);
                break;
            }
        }
    }
    return 0;
}