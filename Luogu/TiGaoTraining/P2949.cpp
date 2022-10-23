#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 5e5 + 100;
struct node
{
    int end,val;
    bool operator<(const node &b) const
    {
        if(this-> end == b.end)
            return this->val > b.val;
        return this-> end < b.end;
    }
}a[maxn];
int n;
int heap[maxn<<1],size;
inline void push(int x)
{
    heap[++size] = x;
    int p = size;
    while(p > 1 && heap[p] < heap[p>>1])
        std::swap(heap[p],heap[p>>1]),p >>= 1;
}
inline void del()
{
    std::swap(heap[1],heap[size--]);
    int x = 1;
    while((x << 1) <= size)
    {
        int t = x << 1;
        if(t < size && heap[t] > heap[t+1]) ++t;
        if(heap[x] <= heap[t])
            break;
        std::swap(heap[x],heap[t]);
        x = t;
    }
}
long long ans;
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(a[i].end),read(a[i].val);
    std::sort(a+1,a+1+n);
    for(int i = 1;i<=n;++i)
        if(a[i].end > size)
            ans += a[i].val,push(a[i].val);
        else if(a[i].val > heap[1])
            ans = ans - heap[1] + a[i].val,push(a[i].val),del();
    printf("%lld",ans);
    return 0;
}