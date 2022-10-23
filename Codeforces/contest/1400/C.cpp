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
const int maxn = 1e5 + 100;
int T,n,x;
char s[maxn],w[maxn],s2[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(s + 1);
        n = strlen(s + 1);
        for (int i = 1; i <= n; ++i) w[i] = '1';
        read(x);
        for(int i = 1;i<=n;++i) if(s[i] == '0') 
        {
            if(i - x >= 1) w[i-x] = '0';
            if(i + x <= n) w[i+x] = '0';
        }
        for(int i = 1;i<=n;++i)
        {
            if(i - x >= 1 && i + x <= n) s2[i] = (w[i-x] == '0' && w[i+x] == '0') ?  '0' : '1';
            else if(i - x >= 1) s2[i] = w[i-x];
            else if(i + x <= n) s2[i] = w[i+x];
            else s2[i] = '0';
        }
        for (int i = 1; i <= n; ++i) if(s[i] != s2[i]) goto fail;
        for(int i = 1;i<=n;++i) putchar(w[i]);
        puts("");
        continue;
        fail:puts("-1");
    }
    return 0;
}