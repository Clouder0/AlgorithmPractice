#include <cstdio>
#include <cstring>
using namespace std;
char buf[1000000],*p1 = buf,*p2 = buf;
#define nc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++)
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=nc();c>'9'||c<'0';c=nc());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
}
void read(char *s)
{
    static char c;
    for(c=nc();c!=')'&&c!='(';c=nc());
    for(;c=='('||c==')';*++s = c,c=nc());
}
int n;
char all[500010];
int fa[500010];
int last[500010],seq[500010];
long long f[500010],ans;
int main()
{
    read(n);
    for(all[1] = nc();all[1]!=')'&&all[1]!='(';all[1]=nc());
    memcpy(all+2,p1,sizeof(char)*(n-1));
    p1 += n;
    if(p1 > p2)
        p1 = p2;
    for(int i = 2;i<=n;++i)
        read(fa[i]);
    for(int i = 1;i<=n;++i)
    {
        f[i] = f[fa[i]];
        last[i] = last[fa[i]];
        if(all[i] == '(')
            last[i] = i;
        else if(last[i])
        {
            seq[i] = seq[fa[last[i]]] + 1;
            last[i] = last[fa[last[i]]];
            f[i] += seq[i];
        }
        ans ^= i * f[i];
    }
    printf("%lld",ans);
    return 0;
}