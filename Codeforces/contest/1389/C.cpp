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
const int maxn = 2e5 + 100;
int T;
char s[maxn];
int main()
{
    read(T);
    while(T--)
    {
        read(s + 1);
        int n = strlen(s + 1),res = 0;
        for(char i = '0';i<='9';++i) for(char j = '0';j<='9';++j)
        {
            int last = 1,ans = 0;
            for(int k = 1;k<=n;++k)
            {
                if(last)
                {
                    if (s[k] == i) last ^= 1, ++ans;
                }
                else
                {
                    if(s[k] == j) last ^= 1,++ans;
                }
            }
            if(i != j && (ans & 1)) --ans;
            res = std::max(res,ans);
        }
        printf("%d\n",n - res);
    }
    return 0;
}