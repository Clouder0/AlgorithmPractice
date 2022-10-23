#include <algorithm>
#include <cstdio>
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
inline void read(char* s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template <typename T>
inline T read(T& r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 4e5 + 100;
int T, n;
char s[maxn];
int len[maxn];
int main()
{
    read(T);
    while (T--)
    {
        read(n);
        read(s + 1);
        for (int i = 1; i <= n; ++i) s[i + n] = s[i];
        int ans = (n + 2) / 3;
        for (int i = 1; i <= n; ++i)
        {
            if (s[i] != s[i + n - 1])
            {
                int res = 0;
                len[i - 1] = 0;
                for (int j = i; j <= i + n - 1; ++j)
                    if (s[j] == s[j - 1]) len[j] = len[j - 1] + 1;
                    else len[j] = 1, res += len[j - 1] / 3;
                res += len[i + n - 1] / 3;
                ans = res;
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}