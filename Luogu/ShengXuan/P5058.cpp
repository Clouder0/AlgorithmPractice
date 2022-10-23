#include <cstdio>
#include <queue>
#include <cstring>
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
}lines[100000];
int head[110];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    lines[++tot] = node(y,head[x]),head[x] = tot;
}
int n;
int s,t;
bool vis[110];
void bfs()
{
    queue<int> q;
    int u,v;
    q.push(s);
    vis[s] = true;
    while(!q.empty())
    {
        u = q.front();
        q.pop();
        for(int p = head[u];p;p=lines[p].next)
        {
            v = lines[p].to;
            if(!vis[v])
            {
                vis[v] = true;
                q.push(v);
            }
        }
    }
}
int main()
{
    read(n);
    int x,y;
    do
    {
        read(x);
        read(y);
        add(x,y);
        add(y,x);
    }while(x != 0 && y != 0);
    read(s);
    read(t);
    for(int i = 1;i<=n;++i)
    {
        if(i == s || i == t)
            continue;
        memset(vis,0,sizeof(vis));
        vis[i] = true;
        bfs();
        if(!vis[t])
        {
            printf("%d",i);
            return 0;
        }
    }
    printf("No solution");
    return 0;
}