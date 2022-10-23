#include <cstdio>
using namespace std;
int fa[1001000];
int rnk[1001000];
char all[2][1010];
int n, m;
inline char nc()
{
    static char buf[100000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
void read(char *s)
{
    static char c;
    for(c=nc();c>'1'||c<'0';c=nc());
    for(;c=='0'||c=='1';*++s=c,c=nc());
}
void read(int &r)
{
    static char c; r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
inline int find(const int &x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void unite(const int &a, const int &b)
{
    int t1 = find(a), t2 = find(b);
    if (t1 == t2)
        return;
    rnk[t1] > rnk[t2] ? fa[t2] = t1 : fa[t1] = t2; //按秩合并
    rnk[t1] = rnk[t2] = rnk[t1] + rnk[t2];
}
void init()
{
    read(n);
    read(m);
    int n2 = n * n;
    for (int i = 1; i <= n2; ++i)
        fa[i] = i, rnk[i] = 1;
}
int main()
{
    init();
    //每个点只需要判断其左其上即可
    int now = 1, pre = 0;
    for (int i = 1; i <= n; ++i)
    {
        now ^= 1;
        pre ^= 1;
        read(all[now]);
        for (int j = 1; j <= n; ++j)
        {
            if (j - 1 > 0 && all[now][j] != all[now][j - 1])
                unite((i - 1) * n + j, (i - 1) * n + j - 1);
            if (i - 1 > 0 && all[now][j] != all[pre][j])
                unite((i - 1) * n + j, (i - 2) * n + j);
        }
    }
    int x, y;
    for (int i = 1; i <= m; ++i)
    {
        read(x);
        read(y);
        printf("%d\n", rnk[find((x - 1) * n + y)]);
    }
    return 0;
}