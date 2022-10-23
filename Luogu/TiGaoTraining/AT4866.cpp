#include <cstdio>
#include <algorithm>
#include <cstring>
#include <ctype.h>
const int bufSize = 1e6;
using std::min;
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
const int maxn = 1e6 + 100;
char s[maxn];
int n, f[maxn][2];
int main()
{
    read(s + 1);
    n = strlen(s + 1);
    for (int i = 1; i <= n; ++i) s[i] -= '0';
    f[n][0] = s[n],f[n][1] = 10 - s[n];
    for(int i = n - 1;i > 0;--i)
    {
        f[i][1] = min(f[i + 1][0] + 10 - s[i], f[i + 1][1] + 9 - s[i]);
        if (s[i] != '9') f[i][0] = min(f[i + 1][0] + s[i], f[i + 1][1] + s[i] + 1);
        else f[i][0] = f[i + 1][0] + s[i];
    }
    printf("%d\n",min(f[1][0],f[1][1] + 1));
    return 0;
}