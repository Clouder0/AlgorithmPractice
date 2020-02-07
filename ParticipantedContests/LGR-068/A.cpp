#include <cstdio>
#include <algorithm>
#include <memory.h>
#include <set>
using namespace std;
struct node
{
    int to,next;
    node(){}
    node(const int &_to,const int &_next) : to(_to),next(_next){}
}E[1000000];
int head[2100];
int tot;
inline void add(const int &x,const int &y)
{
    E[++tot] = node(y,head[x]),head[x] = tot;
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n,m,ans;
bool dis[2100][2100];
struct point
{
    int pts[4];
    point(){}
    point(int a,int b,int c)
    {
        pts[1] = a,pts[2] = b,pts[3] = c;
        sort(pts+1,pts+4);
    }
    bool operator<(const point &b) const
    {
        if(pts[1] != b.pts[1])
            return pts[1] < b.pts[1];
        if(pts[2] != b.pts[2])
            return pts[2] < b.pts[2];
        if(pts[3] != b.pts[3])
            return pts[3] < b.pts[3];
        return false;
    }
};
set<point> res;
int main()
{
    read(n);
    read(m);
    int x,y;
    for(int i = 1;i<=m;++i)
    {
        read(x);
        read(y);
        add(x,y);
        add(y,x);
        dis[x][y] = dis[y][x] = 1;
    }
    // a b c
    int a,b,c;
    for(a = 1;a<=n;++a)
    {
        for(int p = head[a];p;p=E[p].next)
        {
            b = E[p].to;
            if(a == b)
                continue;
            for(int q = head[b];q;q=E[q].next)
            {
                if(a == c || b == c)
                    continue;
                c = E[q].to;
                if(dis[a][c] == 1)
                {
                    res.insert(point(a,b,c));
                    break;
                }
            }
        }
    }
    tot = 0;
    memset(head,0,sizeof(head));
    for(int i = 1;i<=n;++i)
        for(int j = i+1;j<=n;++j)
            if(dis[i][j] == 0)
                add(i,j),add(j,i);
    for (a = 1; a <= n; ++a)
    {
        for(int p = head[a];p;p=E[p].next)
        {
            b = E[p].to;
            if(a == b)
                continue;
            for(int q = head[b];q;q=E[q].next)
            {
                c = E[q].to;
                if(a == c || b == c)
                    continue;
                if(dis[a][c] == 0)
                {
                    res.insert(point(a,b,c));
                }
            }
        }
    }
    printf("%d\n",res.size());
    for(set<point>::iterator it = res.begin();it!=res.end();++it)
        printf("%d %d %d\n",it->pts[1],it->pts[2],it->pts[3]);
    return 0;
}