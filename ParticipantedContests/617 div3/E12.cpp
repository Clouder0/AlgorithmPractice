#include <cstdio>
#include <memory.h>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
struct node
{
    int to,next;
    node(){}
    node(const int &_to,const int &_next) : to(_to),next(_next){}
}E[100000];
int head[2000];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    E[++tot] = node(y,head[x]),head[x] = tot;
}
int n;
char s[210];
int col[210];
bool flag;
void dfs(int u,int from)
{
    col[u] = col[from]^1;
    if(flag)
        return;
    int v;
    for(int p = head[u];p;p=E[p].next)
    {
        v = E[p].to;
        if(col[v] == -1)
            dfs(v,u);
        else if(col[v] == col[u])
        {
            flag = true;
            return;
        }
    }
}
int main()
{
    read(n);
    scanf("%s",s+1);
    for(int i = 1;i<=n;++i)
        for(int j = i+1;j<=n;++j)
            if(s[i] > s[j])
            {
                add(i,j);
                add(j,i);
            }
    memset(col,-1,sizeof(col));
    col[0] = 1;
    for(int i = 1;i<=n;++i)
        if(col[i] == -1)
            dfs(i,0);
    if(flag)
        puts("NO");
    else
    {
        puts("YES");
        for(int i = 1;i<=n;++i)
            putchar(col[i]+48);
    }
    return 0;
}