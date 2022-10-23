#include <cstdio>
template<typename T>
inline void swap(T &a,T &b)
{
    T t = a;
    a = b;
    b = t;
}
template<typename T>
inline T read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
    return r;
}
const int maxn = 5e6 + 10;
int n,m;
int a[maxn];
int size;
inline void up(int x){while(x > 1 && a[x] < a[x>>1]) swap(a[x],a[x>>1]),x >>= 1;}
inline void down(int x)
{
    while((x << 1) <= size)
    {
        int t = x << 1;
        if(t < size && a[t + 1] < a[t]) ++t; //选择儿子中较小的替换父亲以维持性质
        if(a[t] >= a[x]) break;
        swap(a[x],a[t]);
        x = t;
    }
}
inline void push(int x)
{
    a[++size] = x;
    up(size);
}
inline void del()
{
    swap(a[size],a[1]);
    --size;
    down(1);
}
int main()
{
    read(n);
    int t,b;
    while(n--)
    {
        read(t);
        if(t == 1)
            read(b),push(b);
        else if(t == 2)
            printf("%d\n",a[1]);
        else
            del();
    }
    return 0;
}