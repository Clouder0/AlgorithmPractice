#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e6 + 100;
const int maxk = 70;
struct node
{
    int pos,color;
}A[maxn];
int cnt[maxk],kind;
int n,k,tot;
bool cmp(const node &a,const node &b){return a.pos < b.pos;}
inline void add(int color)
{
    cnt[color]++;
    if(cnt[color] == 1) ++kind;
}
inline void del(int color)
{
    cnt[color]--;
    if(cnt[color] == 0) --kind;
}
int main()
{
    read(n),read(k);
    for(int i = 1;i<=k;++i)
    {
        int num;
        read(num);
        while(num--) read(A[++tot].pos),A[tot].color = i;
    }
    std::sort(A + 1,A + 1 + n,cmp);
    int l = 1,r = 0;
    int ans = 1<<30;
    while(r <= n)
    {
        while(r < n && kind < k) add(A[++r].color);
        if(kind < k) break;
        while(cnt[A[l].color] > 1) del(A[l++].color);
        if(A[r].pos - A[l].pos < ans) ans = A[r].pos - A[l].pos;
        del(A[l++].color);
    }
    printf("%d",ans);
    return 0;
}