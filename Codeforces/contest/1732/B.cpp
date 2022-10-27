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
const int maxn = 2e5 + 100;
int T, n, a[maxn], cnt;
int pre[maxn], suf[maxn];
char s[maxn];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%s",&n,s + 1);
        cnt = 0;
        for (int i = 2; i <= n; ++i)
            if (s[i] != s[i - 1]) a[++cnt] = s[i - 1] - '0';
        a[++cnt] = s[n] - '0';
        int res = 1 << 30;
        int need = !a[cnt];
        suf[cnt] = !a[cnt];
        suf[cnt + 1] = 0;
        for (int i = cnt - 1; i >= 1; --i)
        {
            if (a[i] == 0) need += 2;
            suf[i] = need;
        }
        need = 2 * a[1];
        pre[0] = 0;
        pre[1] = 2 * a[1];
        for (int i = 2; i <= cnt; ++i)
        {
            if (a[i]) need += 2;
            pre[i] = need;
        }
//        for(int i = 0;i<=cnt;++i) printf("%d ",pre[i]);
//        puts("pre");
//        for(int i = 0;i<=cnt;++i) printf("%d ",suf[i]);
//        puts("suf");
        for (int i = 0; i <= cnt; ++i) res = std::min(res, pre[i] + suf[i + 1]);
        printf("%d\n", res);
    }
    return 0;
}