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
inline T _max(const T &a,const T &b){return a>b?a:b;}
const int maxn = 26000;
int n,T;
struct node
{
    int id;
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
    read(n);
    for (int i = 1; i <= n; ++i)
        read(all[i].a),all[i].id = i;
    for(int i = 1;i<=n;++i)
        read(all[i].b);
    sort(all + 1, all + 1 + n, cmp);
    long long s1(0), s2(0);
    for (int i = 1; i <= n; ++i)
    {
        s1 += all[i+1].a;
        s2 += all[i].b;
    }
    printf("%lld\n", all[1].a + all[n].b + max(s1,s2));
    for(int i = 1;i<=n;++i)
        printf("%d ",all[i].id);
    return 0;
}