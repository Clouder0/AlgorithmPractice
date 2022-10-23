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
const int maxn = 4e3 + 100;
int T,n;
int a[maxn];
int w[maxn],f[maxn],tot;
int main()
{
    read(T);
    while(T--)
    {
        tot = 0;
        read(n);
        n <<= 1;
        for (int i = 1; i <= n; ++i) read(a[i]);
        for(int i = 1;i<=n;++i)
        {
            w[++tot] = 1;
            int j;
            for(j = i + 1;j<=n;++j)
            {
                if(a[j] >= a[i]) break;
                w[tot]++;
            }
//            printf("%d %d w[%d]:%d\n",i,j,tot,w[tot]);
            i = j - 1;
        }
//        for(int i = 1;i<=tot;++i) printf("%d ",w[i]);
//        putchar('\n');
//        printf("tot:%d\n",tot);
        for (int i = 1; i <= n; ++i) f[i] = 0;
        f[0] = 1;
//        for(int i = 1;i<=tot;++i) printf("%d\n",w[i]);
        
        for(int i = 1;i<=tot;++i) for (int j = n; j >= w[i]; --j) f[j] |= f[j - w[i]];
        if(f[n/2]) puts("YES");
        else puts("NO");
    }
    return 0;
}