#include <algorithm>
#include <cstdio>
#include <ctype.h>
#include <iostream>
#include <string>
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
inline void read(char* s)
{
    static char c;
    for (; !isalpha(c); c = nc())
        ;
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
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
const int maxn = 5100;
int n;
char a[maxn], b[maxn];
std::string s[maxn];
char rev(char t)
{
    return t == 'p' ? 'd' : 'p';
}
int main()
{
    read(n);
    read(a + 1);
    int l = 1;
    while (a[l] == 'd') ++l;
    if (l > n)
    {
        puts(a + 1);
        return 0;
    }
    int cnt = 0;
    s[++cnt] = a + l;
    for (int r = l; r <= n; ++r)
    {
        int p = 0;
        for (int i = r; i >= l; --i)
            b[p++] = rev(a[i]);
        b[p++] = '\0';
        s[++cnt] = b;
        s[cnt] = s[cnt] + (a + l + p - 1);
    }
    std::sort(s + 1, s + 1 + cnt);
    for (int i = 1; i < l; ++i) putchar(a[i]);
    //    puts("");
    // int len = s[1].length();
    printf("%s", s[1].c_str());
    //    puts("");
    // for (int i = l + len; i <= n; ++i) putchar(a[i]);
    return 0;
}