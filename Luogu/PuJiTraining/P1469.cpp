#include <cstdio>
const int bufSize = 1e4;
inline char nc()
{
    static char buf[bufSize],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf) + fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
int read()
{
    static char c;
    int r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
    return r;
}
int n;
int a;
int main()
{
    n = read();
    for(int i = 1;i<=n;++i) a ^= read();
    printf("%d",a);
    return 0;
}