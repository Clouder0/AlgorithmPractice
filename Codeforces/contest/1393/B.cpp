#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
#define DEBUG
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
    for (; c != '+' && c != '-'; c = nc());
    for (; c == '+' || c == '-'; c = nc()) *s++ = c;
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
int n,m;
int cnt[maxn],num[5];
inline void add(int x)
{
    if(cnt[x] < 4) num[cnt[x]]--,num[++cnt[x]]++;
    else
    {
        num[4] -= cnt[x] / 4;
        num[cnt[x] % 4]--;
        ++cnt[x];
        num[4] += cnt[x] / 4;
        num[cnt[x] % 4]++;
    }
}
inline void dele(int x)
{
    if(cnt[x] <= 4) num[cnt[x]]--,num[--cnt[x]]++;
    else
    {
        num[4] -= cnt[x] / 4;
        num[cnt[x] % 4]--;
        --cnt[x];
        num[4] += cnt[x] / 4;
        num[cnt[x] % 4]++;
    }
}
char s[10];
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) 
    {
        int x;
        read(x), add(x);
    }
    read(m);
    while(m--)
    {
        read(s + 1);
        int x; read(x);
        if(s[1] == '+') add(x);
        else if(s[1] = '-') dele(x);
        if(num[4] > 1 || (num[4] == 1 && (num[3] + num[2]) >= 2)) puts("Yes");
        else puts("No");
    }
    return 0;
}