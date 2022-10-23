#include <cstdio>
#include <vector>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
using namespace std;
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
const int maxn = 5e3 + 100;
int n,m;
int del[maxn];
int siz;
int left[maxn],cnt;
int main()
{
    read(n),read(m);
    siz = n;
    while(siz > 3)
    {
        int num = 0;
        for (int i = 1; i <= n; ++i)
        {
            if(del[i]) continue;
            ++num;
            if(num == 2) num = 0,del[i] = 1,--siz;
        }
        if(siz <= 3) break;
        num = 0;
        for (int i = 1; i <= n; ++i) 
        {
            if(del[i]) continue;
            ++num;
            if(num == 3) num = 0,del[i] = 1,--siz;
        }
    }
    for (int i = 1; i <= n; ++i) if(!del[i]) left[++cnt] = i;
    int sum = 0;
    for (int i = 1; i <= cnt; ++i) sum += left[i];
    if(sum > m) 
        for(int i = 1;i<=cnt;++i) printf("%d ",left[i]);
    else
    {
        printf("%d",std::abs(m + sum));
    }
    return 0;
}