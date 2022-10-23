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
int T,a,b,x,y,n;
int main()
{
    read(T);
    while(T--)
    {
        read(a), read(b), read(x), read(y), read(n);
        int t1 = a - x, t2 = b - y;
        if(n >= t1 + t2) {printf("%lld\n",1ll * x * y);continue;}
        long long minn = 1ll * std::max(x,a - n) * (b - std::max(0,n - t1));
        minn = std::min(minn,1ll * std::max(y,b - n) * (a - std::max(0,n - t2)));
        printf("%lld\n",minn);
    }
    return 0;
}