#include <cstdio>
#include <cstring>
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
    for (; !isdigit(c); c = nc());
    for (; isdigit(c); c = nc()) *s++ = c;
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
const int maxn = 110;
int T;
char s[maxn];
int bel[maxn],len[maxn],cnt;
int main()
{
    read(T);
    while(T--)
    {
        read(s + 1);
        int n = strlen(s + 1);
        cnt = 0;
        for (int i = 1; i <= n; ++i) bel[i] = 0;
        for (int i = 1; i <= n; ++i)
            if (s[i] == '1')
            {
                if (s[i] == s[i - 1]) bel[i] = bel[i - 1], len[bel[i]]++;
                else bel[i] = ++cnt, len[cnt] = 1;
            }
        std::sort(len + 1, len + 1 + cnt);
        int flag = 1, ans = 0;
        for (int i = cnt; i > 0; i -= 2) ans += len[i];
        printf("%d\n", ans);
    }
    return 0;
}