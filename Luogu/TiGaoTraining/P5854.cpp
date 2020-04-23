#include <cstdio>
const int bufSize = 1e6;
inline char nc()
{
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline void read(T &r)
{
    static char c;r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
const int maxn = 1e7 + 100;
int n;
int a[maxn],ls[maxn],rs[maxn];
int s[maxn],top;
int main()
{
    read(n);
    for(int i = 1;i<=n;++i)
        read(a[i]);
    for(int i = 1;i<=n;++i)
    {
        while(top && a[s[top]] > a[i])
            ls[i] = s[top--];
        if(s[top])
            rs[s[top]] = i;
        s[++top] = i;
    }
    long long lres = 0,rres = 0;
    for(int i = 1;i<=n;++i)
    {
        lres ^= (long long)i * (ls[i] + 1);
        rres ^= (long long)i * (rs[i] + 1);
    }
    printf("%lld %lld",lres,rres);
    return 0;
}