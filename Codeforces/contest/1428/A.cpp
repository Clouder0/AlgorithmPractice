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
int T, x1, y1, x2, y2;
int main()
{
    read(T);
    while(T--)
    {
        read(x1), read(y1), read(x2), read(y2);
        if(x1 == x2)  printf("%d\n",std::abs(y1 - y2));
        else if(y1 == y2) printf("%d\n",std::abs(x1 - x2));
        else printf("%d\n",std::abs(x1 - x2) + std::abs(y1 - y2) + 2);
    }
    return 0;
}