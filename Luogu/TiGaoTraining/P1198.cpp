#include <cstdio>
using namespace std;
inline char nc()
{
    static char buf[1000000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=nc();c>'9'||c<'0';c=nc()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
    return r*=flag;
}
const int maxn = 2e5 + 10;
int m,d;
long long t,x,num[maxn];
int fa[maxn],q[maxn],tail,cnt;
char flag;
int find(const int &x)
{
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
int main()
{
    read(m);
    read(d);
    while(m--)
    {
        while((flag = nc()) != 'A' && flag != 'Q');
        read(x);
        if(flag == 'A')
        {
            x = (x+t)%d;
            num[++cnt] = x;
            while (tail && num[cnt] >= num[q[tail]])
                fa[q[tail]] = cnt, --tail;
            q[++tail] = fa[cnt] = cnt;
        }
        else
            printf("%lld\n",(t = num[find(cnt-x+1)]));
    }
    return 0;
}