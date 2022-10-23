#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e3;
int k,n;
int has[maxn];
int a[maxn],next[maxn],last[maxn];
struct node
{
    int id,end;
    bool operator<(const node &b) const
    {
        return end < b.end;
    }
};
priority_queue<node> q;
int main()
{
    read(k);
    read(n);
    memset(last,0x3f,sizeof(last));
    for(int i = 1;i<=n;++i)
        read(a[i]);
    for(int i = n;i;--i)
        next[i] = last[a[i]],last[a[i]] = i;
    int x,ans = 0;
    for(int i = 1;i<=n;++i)
    {
        x = a[i];
        node p; p.id = x; p.end = next[i];
        if(has[x])
        {
            q.push(p);
            continue;
        }
        if(q.size() >= k)
        {
            while (q.size() && !has[q.top().id])
                q.pop();
            if(q.empty())
                break;
            has[q.top().id] = 0;
            q.pop();
            ++ans;
        }
        has[x] = 1;
        q.push(p);
    }
    printf("%d",ans);
    return 0;
}