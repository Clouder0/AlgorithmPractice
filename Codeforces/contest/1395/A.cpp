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
long long a[10];
bool check()
{
    int num = 0;
    for(int i = 1;i<=4;++i) if(a[i] & 1) ++num;
    return num <= 1;
}
int main()
{
    read(T);
    while(T--)
    {
        for(int i = 1;i<=4;++i) read(a[i]);
        if(check()) goto suc;
        for (int i = 1; i <= 3; ++i) a[i]--;
        a[4] += 3;
        for (int i = 1; i <= 4; ++i) if (a[i] < 0) goto fail;
        if (check()) goto suc;
        else goto fail;
        suc:
        puts("Yes");
        continue;
        fail: puts("No");
    }
    return 0;
}