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
int T,n;
int main()
{
    read(T);
    while(T--)
    {
        read(n);
        for(int i = 0;3 * i <= n;++i)
            for(int j = 0;3 * i + 5 * j <= n;++j)
                for(int k = 0;3 * i + 5 * j + 7 * k <= n;++k)
                    if(3 * i + 5 * j + 7 * k == n) 
                    {
                        printf("%d %d %d\n",i,j,k);
                        goto end;
                    }
        printf("-1\n");
        continue;
        end:;
    }
    return 0;
}