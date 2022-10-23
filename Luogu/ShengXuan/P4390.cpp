#include <cstdio>
#include <algorithm>
template<typename T>
inline T max(const T &a,const T &b){return a>b?a:b;}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxw = 2e6 + 100;
const int maxn = 2e6 + 100;
struct node
{
    int type,x,y,askid,val,time;
}A[maxn],B[maxn];
int w,tot;
int query[maxn],qtot;
int sum[maxn],vis[maxn],time;
inline void add(int x,int k)
{
    if(x == 0) return;
    while(x <= w)
    {
        if(vis[x] != time) sum[x] = 0,vis[x] = time;
        sum[x] += k;
        x += x & -x;
    }
}
inline int ask(int x)
{
    int res = 0;
    while(x > 0)
    {
        if(vis[x] != time) sum[x] = 0,vis[x] = time;
        res += sum[x];
        x -= x & -x;
    }
    return res;
}
void cdq(int l,int r)
{
    if(l == r) return;
    int mid = l + r >> 1;
    cdq(l,mid),cdq(mid + 1,r);
    int p = l, q = mid + 1,k = l;
    ++time;
    while(p <= mid && q <= r)
    {
        if(A[p].x <= A[q].x)
        {
            add(A[p].y,A[p].val);
            B[k++] = A[p++];
        }
        else
        {
            if(A[q].type != 2) query[A[q].askid] += ask(A[q].y) * A[q].type;
            B[k++] = A[q++];
        }
    }
    while(p <= mid) B[k++] = A[p++];
    while(q <= r)
    {
        if(A[q].type != 2) query[A[q].askid] += ask(A[q].y) * A[q].type;
        B[k++] = A[q++];
    }
    for(int i = l;i<=r;++i) A[i] = B[i];
}
int main()
{
    int opt;
    while(1)
    {
        read(opt);
        if(opt == 0) read(w);
        else if(opt == 1)
        {
            int a,b,c;
            read(a),read(b),read(c);
            A[++tot].type = 2,A[tot].x = a,A[tot].y = b,A[tot].val = c;
        }
        else if(opt == 2)
        {
            int x1,x2,y1,y2;
            read(x1),read(y1),read(x2),read(y2);
            A[++tot].type = 1,A[tot].x = x2,A[tot].y = y2,A[tot].askid = ++qtot;
            A[++tot].type = -1,A[tot].x = x1 - 1,A[tot].y = y2,A[tot].askid = qtot;
            A[++tot].type = -1,A[tot].x = x2,A[tot].y = y1 - 1,A[tot].askid = qtot;
            A[++tot].type = 1,A[tot].x = x1 - 1,A[tot].y = y1 - 1,A[tot].askid = qtot;
        }
        else if(opt == 3) break;
    }
    cdq(1,tot);
    for(int i = 1;i<=qtot;++i)  printf("%d\n",query[i]);
    return 0;
}