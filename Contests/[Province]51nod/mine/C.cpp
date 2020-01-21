#include <cstdio>
#include <queue>
using namespace std;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[1000000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
void read(char *s)
{
    --s;
    static char c;
    for(c=nc();c!='0'&&c!='1';c=nc());
    for(;c=='0'||c=='1';*(++s) = c,c = nc());
    *(++s) = '\0';
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
const int maxn = 101000;
struct node
{
    int to,next;
    node(){}
    node(const int &_to,const int &_next) : to(_to),next(_next){}
}lines[maxn];
int head[maxn];
inline void add(const int &x,const int &y)
{
    static int tot = 0;
    lines[++tot] = node(y,head[x]),head[x] = tot;
}
struct sta
{
    int u,day;
    sta(){}
    sta(const int &_u,const int &_day) : u(_u),day(_day){}
};
bool s[maxn][55];
int dis[maxn][55];
bool vis[maxn][55];
int ans;
queue<sta> q;
int n,m,d;
void dij()
{
    dis[1][0] = s[1][0];
    q.push(sta(1,0));
    sta now;
    int v,nd;
    while(!q.empty())
    {
        now = q.front();
        q.pop();
        if(vis[now.u][now.day])
            continue;
        vis[now.u][now.day] = true;
        if(dis[now.u][now.day] > ans)
            ans = dis[now.u][now.day];
        nd = (now.day + 1) % 7;
        for(int p = head[now.u];p;p=lines[p].next)
        {
            v = lines[p].to;
            if(vis[v][nd])
                continue;
            if(dis[v][nd] < dis[now.u][now.day] + s[v][nd])
            {
                dis[v][nd] = dis[now.u][now.day] + s[v][nd];
                q.push(sta(v,nd));
            }
        }
    }
}
char temp[55];
int main()
{
    read(n);
    read(m);
    read(d);
    int a,b;
    for(;m;--m)
    {
        read(a);
        read(b);
        add(a,b);
    }
    for(int i = 1;i<=n;++i)
    {
        read(temp);
        for(int j = 0;j<d;++j)
            s[i][j] = (temp[j] ^ 48);
    }
    dij();
    printf("%d",ans);
    return 0;
}