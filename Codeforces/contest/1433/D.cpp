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
const int maxn = 5100;
int T, n, bel[maxn], vis[maxn];
int A[maxn], B[maxn], cnt;
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        cnt = 0;
        for (int i = 1; i <= n; ++i) read(bel[i]), vis[i] = 0;
        vis[1] = 1;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (!vis[j] && bel[i] != bel[j]) vis[j] = 1, A[++cnt] = i, B[cnt] = j;
        for (int i = 1; i <= n; ++i) if (!vis[i]) { puts("NO"); goto end; }
        puts("YES");
        for (int i = 1; i <= cnt; ++i) printf("%d %d\n",A[i],B[i]);
        end:;
    }
    return 0;
}