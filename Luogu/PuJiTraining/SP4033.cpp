#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e6 + 100;
int son[maxn][10],val[maxn],tot;
inline void init(int x)
{
    val[x] = 0;
    for(int i = 0;i<10;++i) son[x][i] = 0;
}
inline int insert(char *s)
{
    int u = 0,res = 0;
    while(*s != '\0')
    {
        if(!son[u][*s - 48]) son[u][*s - 48] = ++tot,init(tot);
        if(val[u]) res = 1;
        u = son[u][*s - 48];
        ++s;
    }
    val[u] = 1;
    for(int i = 0;i<10;++i) if(son[u][i]) res = 1;
    return res;
}
char s[maxn];
int T,n;
int main()
{
    read(T);
    while(T--)
    {
        tot = 1, init(0);
        read(n);
        int flag = 0;
        while (n--)
        {
            scanf("%s", s);
            flag |= insert(s);
        }
        if (flag) puts("NO");
        else puts("YES");
    }
    return 0;
}