#include <cstdio>
#include <cstring>
using namespace std;
int fa[27], vis[27];
inline int find(const int &x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void unite(const int &a, const int &b)
{
    int t1 = find(a), t2 = find(b);
    if (t1 == t2)
        return;
    fa[t1] = t2;
}
char all[60];
int n, len,ans;
inline char nc()
{
    static char buf[1050000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1050000,stdin),p1==p2)?EOF:*p1++;
}
void read(char *s)
{
    static char c;
    for(c=nc();c>'z'||c<'a';c=nc());
    for(;c>='a'&&c<='z';*(++s) = c,c=nc());
    *(++s) = '\0';//快读的细节，为了防止上次读入内容影响到，要加文本终止符
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= 26; ++i)
        fa[i] = i;//初始化
    for (int i = 1; i <= n; ++i)
    {
        read(all);
        len = strlen(all + 1);
        for (int j = 1; j <= len; ++j)
            unite(all[j] - 'a' + 1, all[1] - 'a' + 1), vis[all[j] - 'a' + 1] = 1;
    }
    for(int i = 1;i<=26;++i)
        if(vis[i] && find(i) == i)
            ++ans;
    printf("%d",ans);
    return 0;
}