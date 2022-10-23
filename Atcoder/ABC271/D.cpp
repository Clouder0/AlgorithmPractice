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
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
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
const int maxs = 10100;
int n, s, a[maxn], b[maxn];
int choose[maxn][maxs], from[maxn][maxs];
int st[maxn],top;
int main()
{
    read(n), read(s);
    for (int i = 1; i <= n; ++i) read(a[i]), read(b[i]);
    choose[1][a[1]] = 1, choose[1][b[1]] = 2;
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 0; j <= s; ++j)
        {
            if (j - a[i] >= 0 && choose[i - 1][j - a[i]]) choose[i][j] = 1, from[i][j] = j - a[i];
            if (j - b[i] >= 0 && choose[i - 1][j - b[i]]) choose[i][j] = 2, from[i][j] = j - b[i];
        }
    }
    if(choose[n][s]) 
    {
        puts("Yes");
        for (int i = n, p = s; i; --i)
        {
            st[++top] = choose[i][p];
            p = from[i][p];
        }
        while (top) putchar(st[top] == 1 ? 'H' : 'T'), --top;
    }
    else puts("No");
    return 0;
}