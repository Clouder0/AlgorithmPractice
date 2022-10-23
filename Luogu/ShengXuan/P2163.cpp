#include <cstdio>
#include <algorithm>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 3e6 + 100;
struct query
{
    int x,y,type,id;//type 0 = change,1 = del,2 = add
    bool operator<(const query &b) const
    {
        if(this->x != b.x)
            return this->x < b.x;
        if(this->y != b.y)
            return this->y < b.y;
        return this->type < b.type;
    }
}qs[maxn],tmp[maxn];
int tot;
inline void add(const int &x,const int &y,const int &type,const int &id)
{
    qs[++tot] = (query){x,y,type,id};
}
int ans[maxn];
void cdq(int ll,int rr)
{
    if(ll == rr)
        return;
    int mid = (ll+rr)>>1;
    cdq(ll,mid);
    cdq(mid+1,rr);
    int p = ll,q = mid+1;
    int k = 0;
    int res = 0;
    while(p <= mid || q <= rr)
    {
        if(q > rr || (p <= mid && qs[p].y <= qs[q].y))
        {
            if(qs[p].type == 0)
                ++res;
            tmp[++k] = qs[p++];
        }
        else
        {
            if(qs[q].type == 1)
                ans[qs[q].id] -= res;
            else if(qs[q].type == 2)
                ans[qs[q].id] += res;
            tmp[++k] = qs[q++];
        }
    }
    for(int i = 1;i<=k;++i)
        qs[ll+i-1] = tmp[i];
}
int n,m;
int main()
{
    read(n);
    read(m);
    int x,y;
    for(int i = 1;i<=n;++i)
    {
        read(x);
        read(y);
        add(x,y,0,0);
    }
    int xx,yy;
    for(int i = 1;i<=m;++i)
    {
        read(x);
        read(y);
        read(xx);
        read(yy);
        add(x-1,y-1,2,i);
        add(xx,yy,2,i);
        add(x-1,yy,1,i);
        add(xx,y-1,1,i);
    }
    sort(qs+1,qs+1+tot);
    cdq(1,tot);
    for(int i = 1;i<=m;++i)
        printf("%d\n",ans[i]);
    return 0;
}