#include <cstdio>
#include <algorithm>
#include <ctype.h>
const int bufSize = 1e6;
inline char nc()
{
    #ifdef DEBUG
    return getchar();
    #endif
    static char buf[bufSize], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, bufSize, stdin), p1 == p2) ? EOF : *p1++;
}
inline void read(char *s)
{
    static char c;
    for (; !isalpha(c); c = nc());
    for (; isalpha(c); c = nc()) *s++ = c;
    *s = '\0';
}
template<typename T>
inline T read(T &r)
{
    static char c;
    static int flag;
    flag = 1, r = 0;
    for (c = nc(); !isdigit(c); c = nc()) if (c == '-') flag = -1;
    for (; isdigit(c); c = nc()) r = r * 10 + c - 48;
    return r *= flag;
}
const int maxn = 2e5 + 100;
int H[maxn],cnt;
int n,type[maxn],light[maxn],val[maxn];
int num[maxn<<2],lnum[maxn<<2];
long long sum[maxn<<2];
void modify(int l,int r,int p,int pos,int k,int light)
{
    if(l == r)
    {
        num[p] += k;
        if(light) lnum[p] += k;
        sum[p] += 1ll * H[l] * k;
        return;
    }
    int mid = l + r >> 1;
    if(pos <= mid) modify(l,mid,p<<1,pos,k,light);
    else modify(mid + 1,r,p<<1|1,pos,k,light);
    num[p] = num[p<<1] + num[p<<1|1];
    lnum[p] = lnum[p<<1] + lnum[p<<1|1];
    sum[p] = sum[p<<1] + sum[p<<1|1];
}
int left,selectedlight;
long long res = 0;
void ask(int l,int r,int p)
{
    if(num[p] <= left)
    {
        left -= num[p];
        selectedlight += lnum[p];
        res += sum[p];
        return;
    }
    if(l == r)
    {
        res += 1ll * H[l] * left;
        selectedlight += std::max(0,left - (num[p] - lnum[p]));
        return;
    }
    int mid = l + r >> 1;
    ask(mid + 1,r,p<<1|1),ask(l,mid,p<<1);
}
int askkth(int l,int r,int p,int k)
{
    if(k > num[p]) return 0;
    if(l == r) return H[l];
    int t = num[p<<1|1],mid = l + r >> 1;
    if(k <= t) return askkth(mid + 1,r,p<<1|1,k);
    else return askkth(l,mid,p<<1,k - t);
}
int main()
{
    read(n);
    for (int i = 1; i <= n; ++i) read(light[i]),read(val[i]),type[i] = val[i] > 0,val[i] = std::abs(val[i]),H[++cnt] = val[i];
    std::sort(H + 1,H + 1 + cnt),cnt = std::unique(H + 1,H + 1 + cnt) - H - 1;
    for (int i = 1; i <= n; ++i) val[i] = std::lower_bound(H + 1,H + 1 + cnt,val[i]) - H;
    long long sum = 0;
    int lightnum = 0;
    for (int i = 1; i <= n; ++i) 
    {
        if(type[i])
        {
            sum += H[val[i]];
            modify(1,cnt,1,val[i],1,light[i]);
            lightnum += light[i];
        }
        else
        {
            sum -= H[val[i]];
            modify(1,cnt,1,val[i],-1,light[i]);
            lightnum -= light[i];
        }
        left = lightnum,res = 0,selectedlight = 0;
        ask(1,cnt,1);
        if(lightnum && selectedlight == lightnum) 
        {
            res -= askkth(1,cnt,1,lightnum);
            res += askkth(1,cnt,1,lightnum + 1);
        }
        printf("%lld\n",sum + res);
    }
    return 0;
}