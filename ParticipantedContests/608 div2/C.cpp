#include <cstdio>
using namespace std;
inline char nc()
{
    static char buf[1000000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c; r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
int n,p,q;
int l,r,top,bottom;
inline int max(const int &a,const int &b){return a>b?a:b;}
int main()
{
    read(n);
    read(p);
    read(q);
    int x,y;
    for(;n;--n)
    {
        read(x);
        read(y);
        if(x < p)
            ++l;
        else if(x > p)
            ++r;
        if(y > q)
            ++top;
        else if(y < q)
            ++bottom;
    }
    int maxx = max(l,max(r,max(top,bottom)));
    printf("%d\n",maxx);
    if(maxx == l)
        printf("%d %d",p - 1,q);
    else if(maxx == r)
        printf("%d %d",p + 1,q);
    else if(maxx == top)
        printf("%d %d",p,q+1);
    else
        printf("%d %d",p,q-1);
    return 0;
}