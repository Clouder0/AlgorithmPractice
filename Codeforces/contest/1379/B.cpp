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
#define int long long
int T;
long long l,r,m,n,a,b,c,na,bc,x;
inline bool check()
{
    na = n * a;
    bc = m - na;
    if(bc > x || bc < -x) return false;
    if(bc > 0) b = l + bc,c = l;
    else c = r,b = r + bc;
    return true;
}
signed main()
{
    read(T);
    while(T--)
    {
        read(l),read(r),read(m);
        x = r - l;
        for(a = l;a<=r;++a)
        {
            n = m / a;
            if(n && check())
            {
                printf("%lld %lld %lld\n",a,b,c);
                break;
            }
            ++n;
            if(check())
            {
                printf("%lld %lld %lld\n",a,b,c);
                break;
            }
        }
    }
    return 0;
}