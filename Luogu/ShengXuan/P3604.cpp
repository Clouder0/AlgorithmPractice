#include <cstdio>
#include <algorithm>
#include <cmath>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 6e4 + 100;
struct node
{
    int l,r,pos,id;
}Q[maxn];
bool cmp(const node &a,const node &b)
{
    if(a.pos != b.pos) return a.pos < b.pos;
    if(a.pos & 1) return a.r < b.r;
    else return a.r > b.r;
}
int n,m,ans;
char s[maxn];
int ANS[maxn],sum[maxn];
unsigned short cnt[(1<<26) + 100];
inline void add(int x)
{
    ans += cnt[sum[x]];
    cnt[sum[x]]++;
    for(int i = 0;i<26;++i) ans += cnt[sum[x] ^ (1<<i)];
}
inline void del(int x)
{
    cnt[sum[x]]--;
    ans -= cnt[sum[x]];
    for(int i = 0;i<26;++i) ans -= cnt[sum[x] ^ (1<<i)];
}
int main()
{
    read(n),read(m);
    std::scanf("%s",s + 1);
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] ^ (1 << (s[i] - 'a'));
    int size = n / sqrt(m);
    for (int i = 1; i <= m; ++i) read(Q[i].l), read(Q[i].r), Q[i].pos = Q[i].l / size,Q[i].id = i;
    std::sort(Q + 1,Q + 1 + m,cmp);
    int l = 1,r = 0;
    for(int i = 1;i<=m;++i)
    {
        Q[i].l--;
        while(l > Q[i].l) add(--l);
        while(r < Q[i].r) add(++r);
        while(l < Q[i].l) del(l++);
        while(r > Q[i].r) del(r--);
        ANS[Q[i].id] = ans;
    }
    for(int i = 1;i<=m;++i) printf("%d\n",ANS[i]);
    return 0;
}