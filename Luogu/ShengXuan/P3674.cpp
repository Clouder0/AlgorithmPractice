#include <cstdio>
#include <cmath>
#include <algorithm>
#include <bitset>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 100;
int n,m;
int a[maxn];
struct node

{
    int l,r,id,opt,x,pos;
    bool operator<(const node &b) const
    {
        if(pos != b.pos) return pos < b.pos;
        if(pos & 1) return r < b.r;
        return r > b.r;
    }
}Q[maxn];
std::bitset<maxn> now,re;
int cnt[maxn],ANS[maxn];
inline void add(int x)
{
    if(cnt[a[x]]++ == 0) now[a[x]] = 1,re[maxn - a[x]] = 1;
}
inline void del(int x)
{
    if(--cnt[a[x]] == 0) now[a[x]] = 0,re[maxn - a[x]] = 0;
}
int main()
{
    read(n),read(m);
    for(int i = 1;i<=n;++i) read(a[i]);
    int size = n / sqrt(m);
    for (int i = 1; i <= m; ++i) read(Q[i].opt), read(Q[i].l), read(Q[i].r), read(Q[i].x), Q[i].id = i, Q[i].pos = Q[i].l / size;
    std::sort(Q + 1, Q + 1 + m);
    int l = 1,r = 0;
    for(int i = 1;i<=m;++i)
    {
        while(l > Q[i].l) add(--l);
        while(r < Q[i].r) add(++r);
        while(l < Q[i].l) del(l++);
        while(r > Q[i].r) del(r--);
        if(Q[i].opt == 1) ANS[Q[i].id] = (now & (now >> Q[i].x)).any();
        else if(Q[i].opt == 2) ANS[Q[i].id] = (now & (re >> (maxn - Q[i].x))).any();
        else
        {
            for (int j= 1; j * j <= Q[i].x; ++j)
                if (Q[i].x % j == 0 && now[j] && now[Q[i].x / j])
                {
                    ANS[Q[i].id] = 1;
                    break;
                }
        }
    }
    for(int i = 1;i<=m;++i) puts(ANS[i]?"hana":"bi");
    return 0;
}