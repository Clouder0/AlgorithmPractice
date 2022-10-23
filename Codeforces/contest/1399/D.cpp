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
    for (; c != '0' && c != '1'; c = nc());
    for (; c == '0' || c == '1'; c = nc()) *s++ = c;
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
const int maxn = 2e5 + 100;
int T,n;
char s[maxn];
int ones[maxn],zeros[maxn],onenum,zeronum,cnt;
int bel[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        read(s + 1);
        cnt = onenum = zeronum = 0;
        for (int i = 1; i <= n; ++i) 
        {
            if(s[i] == '0')
            {
                if(onenum) bel[i] = ones[onenum],zeros[++zeronum] = ones[onenum--];
                else
                {
                    zeros[++zeronum] = ++cnt;
                    bel[i] = cnt;
                }
            }
            else
            {
                if(zeronum) bel[i] = zeros[zeronum],ones[++onenum] = zeros[zeronum--];
                else
                {
                    ones[++onenum] = ++cnt;
                    bel[i] = cnt;
                }
            }
        }
        printf("%d\n",onenum + zeronum);
        for (int i = 1; i <= n; ++i) printf("%d ",bel[i]);
        putchar('\n');
    }
    return 0;
}