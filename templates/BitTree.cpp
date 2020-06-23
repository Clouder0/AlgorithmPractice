#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
const int maxn = 5e5 + 100;
int n,m;
struct Bit
{
    long long sum[maxn];
    inline int lowbit(const int &x){return x & -x;}
    inline void add(int x,int k)
    {
        for (; x <= n; x += lowbit(x)) sum[x] += k;
    }
    inline long long ask(int x)
    {
        long long res = 0;
        for (; x > 0; x -= lowbit(x)) res += sum[x];
        return res;
    }
}A,B;
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i)
    {
        int x;
        read(x);
        A.add(i,x),A.add(i+1,-x);
        B.add(i,i*x),B.add(i+1,(i+1)*(-x));
    }
    while(m--)
    {
        int opt,x,y,k;
        read(opt),read(x),read(y);
        if(opt == 1) read(k),A.add(x,k),A.add(y + 1,-k),B.add(x,k*x),B.add(y+1,-(y+1)*k);
        else printf("%lld\n",A.ask(y) * (y + 1) - B.ask(y) - (A.ask(x - 1) * x - B.ask(x-1)));
    }
    return 0;
}