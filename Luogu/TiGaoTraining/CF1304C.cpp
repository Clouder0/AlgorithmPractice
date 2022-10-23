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
const int maxn = 110;
int T, n, m, L[maxn], R[maxn], pos[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n),read(m);
        for (int i = 1; i <= n; ++i) read(pos[i]), read(L[i]), read(R[i]);
        for (int i = n; i; --i) pos[i] -= pos[i - 1];
        int l = m, r = m;
        for (int i = 1; i <= n; ++i)
        {
            l = std::max(l - pos[i], L[i]), r = std::min(r + pos[i], R[i]);
            if (l > r) goto fail;
        }
        puts("YES");
        continue;
        fail:
        puts("NO");
    }
    return 0;
}