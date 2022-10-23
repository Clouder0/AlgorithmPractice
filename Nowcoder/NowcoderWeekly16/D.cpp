#include <cstdio>
#include <queue>
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
const int maxn = 1e6 + 100;
const int maxm = 1e6 + 100;
int n,m;
template<typename T>
inline T abs(const T &a){return a > 0 ? a : -a;}
inline double getdis(int x,int t)
{
    if(t == 0) return abs(1.0 * x);
    else if(t == 1) return abs(1.0 / (1.0 - x));
    else return abs(1.0 - 1.0 / x);
}
struct node
{
    int to,next,val;
}E[maxm];
int head[maxn];
inline void add(const int &x,const int &y,const int &val)
{
    static int tot = 0;
    E[++tot].next = head[x],E[tot].to = y,E[tot].val = val,head[x] = tot;
}
double dis[maxn][5];
using namespace std;
struct aaa
{
    int id,t;
    double dis;
    bool operator<(const aaa &b) const{return dis > b.dis;}
};
priority_queue<aaa> q;
bool vis[maxn][5];
inline void dij()
{
    for (int i = 1; i <= n; ++i) dis[i][0] = dis[i][1] = dis[i][2] = 1e30;
    dis[1][0] = 0;
    aaa t;
    t.id = 1,t.t = 0,t.dis = dis[1][0];
    q.push(t);
    while(!q.empty())
    {
        int u = q.top().id;
        int t = q.top().t;
        q.pop();
        if(vis[u][t]) continue;
        vis[u][t] = 1;
        for (int p = head[u]; p; p = E[p].next)
        {
            int v = E[p].to;
            int nt = (t + 1) % 3;
            double nv = getdis(E[p].val,t);
            if(vis[v][nt]) continue;
            if(dis[v][nt] > dis[u][t] + nv)
            {
                dis[v][nt] = dis[u][t] + nv;
                aaa ne;
                ne.id = v,ne.t = nt;
                ne.dis = dis[v][nt];
                q.push(ne);
            }
        }
    }
}
int main()
{
    read(n),read(m);
    while(m--)
    {
        int a,b,c;
        read(a),read(b),read(c);
        add(a,b,c),add(b,a,c);
    }
    dij();
    int viss = (vis[n][0] | vis[n][1] | vis[n][2]);
    double anss = std::min(dis[n][0],dis[n][1]);
    anss = std::min(anss,dis[n][2]);
    if(!viss) puts("-1");
    else printf("%.3f",anss);
    return 0;
}