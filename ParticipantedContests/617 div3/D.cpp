#include <cstdio>
#include <queue>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 2e5 + 100;
int n,a,b,k;
int h[maxn];
priority_queue<int,vector<int>,greater<int> > q;
int main()
{
    read(n);
    read(a);
    read(b);
    read(k);
    for(int i = 1;i<=n;++i)
        read(h[i]);
    int turndamage = a+b;
    int ans = 0;
    for(int i = 1;i<=n;++i)
    {
        h[i] %= turndamage;
        if(h[i] == 0)
            h[i] += turndamage;
        int cost = h[i] / a;
        if(cost * a < h[i])
            ++cost;
        --cost;
        q.push(cost);
    }
    int cost;
    while(!q.empty())
    {
        cost = q.top();
        q.pop();
        if(k < cost)
            break;
        k -= cost;
        ++ans;
    }
    printf("%d",ans);
    return 0;
}