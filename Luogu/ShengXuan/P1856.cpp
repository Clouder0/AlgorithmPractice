#include <cstdio>
#include <algorithm>
template<typename T>
inline T abs(const T &a){return a<0?-a:a;}
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
const int maxn = 1e4;
struct Line
{
    int l,r,h,mark;
    bool operator<(const Line &b)
    {
        if(this->h != b.h)
            return this-> h < b.h;
        return this->mark > b.mark;
    }
}E[maxn<<2];
struct node
{
    int l,r,mark,num,len,lflag,rflag;
}a[maxn<<2];
int n;
int X[maxn<<2];
inline void pushup(const int &p)
{
    node &now = a[p],&ls = a[p<<1],&rs = a[p<<1|1];
    if(now.mark)
    {
        now.len = X[now.r + 1] - X[now.l];
        now.num = 1;
        now.lflag = now.rflag = 1;
    }
    else
    {
        now.len = ls.len + rs.len;
        now.num = ls.num + rs.num - (ls.rflag && rs.lflag);
        now.lflag = ls.lflag,now.rflag = rs.rflag;
    }
}
void modify(const int &p,const int &ll,const int &rr,const int &k)
{
    node &now = a[p],&ls = a[p<<1],&rs = a[p<<1|1];
    if(X[now.l] >= ll && X[now.r + 1] <= rr)
    {
        now.mark += k;
        pushup(p);
        return;
    }
    if(ll <= X[ls.r]) modify(p<<1,ll,rr,k);
    if(rr >= X[rs.l + 1]) modify(p<<1|1,ll,rr,k);
    pushup(p);
}
void build(const int &l,const int &r,const int &p)
{
    a[p].l = l,a[p].r = r;
    if(l == r) return;
    int mid = l + r >> 1;
    build(l,mid,p<<1),build(mid + 1,r,p<<1|1);
}
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
    {
        int x1,y1,x2,y2;
        read(x1),read(y1),read(x2),read(y2);
        E[(i<<1) - 1] = (Line){x1,x2,y1,1};
        E[i<<1] = (Line){x1,x2,y2,-1};
        X[(i<<1) - 1] = x1,X[i<<1] = x2;
    }
    std::sort(E + 1,E + 1 + n * 2);
    std::sort(X+1,X+1+n*2);
    int num = std::unique(X + 1,X + 1 + n * 2) - X - 1;
    build(1,num - 1,1);
    long long ans = 0,last = 0;
    for(int i = 1;i<=n*2;++i)
    {
        modify(1,E[i].l,E[i].r,E[i].mark);
        while(E[i+1].h == E[i].h && E[i+1].mark == E[i].mark) ++i,modify(1,E[i].l,E[i].r,E[i].mark);
        ans += abs(last - a[1].len),last = a[1].len;
        ans += 2 * (E[i+1].h - E[i].h) * a[1].num;
    }
    printf("%lld",ans);
    return 0;
}