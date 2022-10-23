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
long long X,K,D;
int main()
{
    read(X),read(K),read(D);
    X = std::abs(X);
    long long steps = X / D;
    if(steps >= K)
    {
        printf("%lld\n",X - K * D);
        return 0;
    }
    K -= steps;
    long long mina = X - steps * D, minb = std::abs(mina - D);
    if(K & 1) printf("%lld\n",minb);
    else printf("%lld\n",mina);
    return 0;
}