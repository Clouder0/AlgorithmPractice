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
const int maxn = 1e5 + 100;
struct node
{
    int type, pos, val, l, r, id;
} Q[maxn * 3], q1[maxn * 3], q2[maxn * 3];
int n, m, sum[maxn], vis[maxn], tim, ans[maxn], cnt, a[maxn];
inline void clear() { ++tim; }
inline void check(int x){if(vis[x] != tim) sum[x] = 0,vis[x] = tim;}
inline void add(int x,int k)
{
    for(;x <= n;x += x & -x) check(x),sum[x] += k;
}
inline int ask(int x)
{
    int res = 0;
    for(;x > 0;x-= x & -x) check(x),res += sum[x];
    return res;
}
void solve(int l, int r, int L, int R)
{
	//printf("%d\n",++solvetime);
	if(L > R) return;
    if(l == r)
    {
        for (int i = L; i <= R; ++i) if(Q[i].type) ans[Q[i].id] = l;
        return;
    }
    int mid = (l + r) >> 1, cnt1 = 0, cnt2 = 0;
    for (int i = L; i <= R; ++i)
    {
        if(Q[i].type)
        {
            //query
            int num = ask(Q[i].r) - ask(Q[i].l - 1);
            if(num >= Q[i].val) q1[++cnt1] = Q[i];
            else Q[i].val -= num,q2[++cnt2] = Q[i];
        }
        else
        {
            if (Q[i].val <= mid) add(Q[i].pos, Q[i].l), q1[++cnt1] = Q[i];
            else q2[++cnt2] = Q[i];
        }
    }
    clear();
    for (int i = 1; i <= cnt1; ++i) Q[L + i - 1] = q1[i];
    for (int i = 1; i <= cnt2; ++i) Q[L + cnt1 + i - 1] = q2[i];
    solve(l, mid, L, L + cnt1 - 1), solve(mid + 1, r, L + cnt1, R);
}
int main()
{
    read(n),read(m);
    for (int i = 1; i <= n; ++i) Q[++cnt].type = 0, Q[cnt].pos = i, Q[cnt].val = read(a[i]), Q[cnt].l = 1;
    int qnum = 0;
    for (int i = 1,x,val; i <= m; ++i)
    {
        char opt[5];
        read(opt);
        if(opt[0] == 'Q') Q[++cnt].type = 1,read(Q[cnt].l),read(Q[cnt].r),read(Q[cnt].val),Q[cnt].id = ++qnum;
        else
        {
            read(x), read(val), Q[++cnt].type = 0, Q[cnt].pos = x, Q[cnt].val = a[x], Q[cnt].l = -1;
            a[x] = val, Q[++cnt].type = 0, Q[cnt].pos = x, Q[cnt].val = a[x], Q[cnt].l = 1;
        }
    }
    solve(0,1000000000,1,cnt);
    for (int i = 1; i <= qnum; ++i) printf("%d\n",ans[i]);
    //printf("%d\n",solvetime);
    return 0;
}