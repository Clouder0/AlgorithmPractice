#include <cstdio>
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
int T,n,x,t;
const int mod = 10000103;
int mp[mod + 1000];
int mpv[mod + 1000];
inline int hash(int val) 
{ 
    int res = (val + 121361) % mod;
    if(res < 0) res += mod;
    return res;
}
inline bool find(int val)
{
    int p = hash(val);
    while (mpv[p] == t && mp[p] != val) p = hash(p);
    if (mpv[p] == t && mp[p] == val) return true;
    return false;
}
inline void ins(int pos)
{
    int p = hash(pos);
    while(mpv[p] == t) p = hash(p);
    mp[p] = pos,mpv[p] = t;
}
const int maxn = 5e4 + 100;
int main()
{
    read(T);
    while(T--)
    {
        ++t;
        read(n);
        while (n--)
        {
            read(x);
            if (find(x)) continue;
            printf("%d ", x);
            ins(x);
        }
        puts("");
    }
    return 0;
}