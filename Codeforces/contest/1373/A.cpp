
// Problem : A. Donut Shops
// Contest : Codeforces - Educational Codeforces Round 90 (Rated for Div. 2)
// URL : https://codeforces.com/contest/1373/problem/A
// Memory Limit : 256 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

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
int T;
long long a,b,c;
const double eps = 1e-9;
int main()
{
    read(T);
    while(T--)
    {
        read(a),read(b),read(c);
        if(a >= c) {printf("-1 %d\n",b);continue;}
        if(b == 1)
        {
            if(a > c) puts("-1 1");
            else if(a < c) puts("1 -1");
            else puts("-1 -1");
            continue;
        }
        double val = 1.0 * c / b;
        if(val > a) puts("1 -1");
        else if(val - a < eps && a - val < eps) puts("1 -1");
        else if(val < a) printf("1 %d\n",b);
    }
    return 0;
}