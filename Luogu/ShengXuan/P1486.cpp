#include <cstdio>
#include <cstring>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;static int flag;flag = 1,r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar()) if(c == '-') flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    r *= flag;
}
const int maxn = 1e6 + 100;
int n,minX;
int sum[maxn<<2];
int A[maxn],extra;
inline void pushup(const int &p){sum[p] = sum[p<<1] + sum[p<<1|1];}
void add(const int &l,const int &r,const int &p,const int &k)
{
    if(l == r)
    {
        sum[p]++;
        return;
    }
    int mid = l + r >> 1;
    if(k <= mid)
        add(l,mid,p<<1,k);
    else
        add(mid + 1,r,p<<1|1,k);
    pushup(p);
}
int ask(const int &l,const int &r,const int &p,int k)
{
    if(l == r)
        return l;
    int mid = l + r >> 1;
    if(k <= sum[p<<1])
        return ask(l,mid,p<<1,k);
    else
        return ask(mid + 1,r,p<<1|1,k - sum[p<<1]);
}
void set(const int &l,const int &r,const int &p)
{
    if(l == r)
    {
        if(l + extra >= minX)
            A[l+extra + 10] = sum[p];
        sum[p] = 0;
        return;
    }
    int mid = l + r >> 1;
    set(l,mid,p<<1);
    set(mid + 1,r,p<<1|1);
}
void build(const int &l,const int &r,const int &p)
{
    if(l == r)
    {
        sum[p] = A[l + 10];
        return;
    }
    int mid = l + r >> 1;
    build(l,mid,p<<1);
    build(mid + 1,r,p<<1|1);
    pushup(p);
}
const int maxR = 2e5 + 100;
int main()
{
    read(n),read(minX);
    char s[5];
    int num = 0;
    for(int i = 1;i<=n;++i)
    {
        int x;
        scanf("%s",s);
        read(x);
        if(s[0] == 'I')
        {
            if(x < minX)
                continue;
            ++num;
            add(0,maxR,1,x);
        }
        else if(s[0] == 'A' || s[0] == 'S')
        {
            memset(A,0,sizeof(A));
            extra = (s[0] == 'A' ? 1 : -1) * x;
            set(0,maxR,1);
            build(0,maxR,1);
        }
        else
        {
            if(x > sum[1])
            {
                puts("-1");
                continue;
            }
            printf("%d\n",ask(0,maxR,1,sum[1] - x + 1));
        }
    }
    printf("%d",num - sum[1]);
    return 0;
}