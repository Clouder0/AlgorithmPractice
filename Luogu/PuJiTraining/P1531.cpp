#include <cstdio>
using namespace std;
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
inline int read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    return r;
}
const int maxn = 2e5 + 10;
int n,m;
int maxx[maxn<<2];
inline void push_up(const int &p)
{
    maxx[p] = max(maxx[p<<1],maxx[p<<1|1]);
}
void build(int l,int r,int p)
{
    if(l == r)
    {
        read(maxx[p]);
        return ;
    }
    int mid = l + r >> 1;
    build(l,mid,p<<1);
    build(mid+1,r,p<<1|1);
    push_up(p);
}
int ll,rr;
int ask(int l,int r,int p)
{
    if(ll <= l && rr >= r)
        return maxx[p];
    int mid = l+r>>1;
    int res = -(1<<30);
    if(ll <= mid)
        res = ask(l,mid,p<<1);
    if(rr > mid)
        res = max(res,ask(mid+1,r,p<<1|1));
    return res;
}
int target,k;
void modify(int l,int r,int p)
{
    if(l == r)
    {
        maxx[p] = max(maxx[p],k);
        return;
    }
    int mid = l+r>>1;
    if(target <= mid)
        modify(l,mid,p<<1);
    else
        modify(mid+1,r,p<<1|1);
    push_up(p);
}
int main()
{
    read(n);
    read(m);
    build(1,n,1);
    char s[10];
    int x,y;
    while(m--)
    {
        scanf("%s%d%d",s,&x,&y);
        if(s[0] == 'Q')
        {
            ll = x,rr = y;
            printf("%d\n",ask(1,n,1));
        }
        else
        {
            target = x,k = y;
            modify(1,n,1);
        }
    }
    return 0;
}