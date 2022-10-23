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
template<typename T>
inline T _min(const T &a,const T &b){return a<b?a:b;}
const int maxn = 21000;
int n,T;
struct node
{
    int a,b;
}all[maxn];
bool cmp(const node &x,const node &y)
{
    if(_min(x.a,y.b) == _min(y.a,x.b))
        return x.a < y.a;
    return _min(x.a,y.b) < _min(y.a,x.b);
}
int main()
{
    read(T);
    for(;T;--T)
    {
        read(n);
        for(int i = 1;i<=n;++i)
            read(all[i].a),read(all[i].b);
        sort(all+1,all+1+n,cmp);
        long long s(0),last(0);
        for(int i = 1;i<=n;++i)
        {
            s += all[i].a;
            last = max(s,last) + all[i].b;
        }
        printf("%lld\n",last);
    }
    return 0;
}