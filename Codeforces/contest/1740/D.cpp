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
const int maxn = 1e6 + 100;
int T, n, m, k, a[maxn], has[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n), read(m), read(k);
        for (int i = 1; i <= k; ++i) read(a[i]), has[i] = 0;
        int num = 0, top = k;
        for (int i = 1; i <= k; ++i)
        {
            ++num, has[a[i]] = 1;
            if(num >= n * m - 2) goto no;
            while (has[top]) has[top--] = 0, --num;
        }
        puts("YA");
        continue;
        no:
        puts("TIDAK");
    }
    return 0;
}