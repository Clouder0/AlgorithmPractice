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
const int maxn = 1e5 + 100;
int n, A, B, C, opt[maxn], sum[4][maxn];
int AB, AC, BC;
char ans[maxn];
int main()
{
    read(n), read(A), read(B), read(C);
    for (int i = 1; i <= n; ++i)
    {
        static char s[10];
        read(s);
        if (s[0] == 'A' && s[1] == 'B') opt[i] = 1;
        else if (s[0] == 'B' && s[1] == 'C') opt[i] = 2;
        else if (s[0] == 'A' && s[1] == 'C') opt[i] = 3;
    }
    for (int i = 1; i <= n; ++i)
    {
        if(opt[i] == 1)
        {
            if (A > B) ans[i] = 'B', --A, ++B;
            else if(A < B) ans[i] = 'A', --B, ++A;
            else
            {
                if (opt[i + 1] == 3) ans[i] = 'A', ++A, --B;
                else ans[i] = 'B', ++B, --A;
            }
        }
        else if(opt[i] == 2)
        {
            if (B > C) ans[i] = 'C', ++C, --B;
            else if(B < C) ans[i] = 'B', ++B, --C;
            else
            {
                if (opt[i + 1] == 1) ans[i] = 'B', ++B, --C;
                else ans[i] = 'C', ++C, --B;
            }
        }
        else
        {
            if (A > C) ans[i] = 'C', ++C, --A;
            else if (A < C) ans[i] = 'A', ++A, --C;
            else
            {
                if (opt[i + 1] == 1) ans[i] = 'A', ++A, --C;
                else ans[i] = 'C', ++C, --A;
            }
        }
        if (A < 0 || B < 0 || C < 0) goto fail;
    }
    puts("Yes");
    for (int i = 1; i <= n; ++i) printf("%c\n", ans[i]);
    return 0;
fail:
    puts("No");
    return 0;
}