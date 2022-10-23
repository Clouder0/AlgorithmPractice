#include <cstdio>
#include <algorithm>
using namespace std;
inline char nc()
{
    static char buf[1000000],*p1 = buf,*p2 = buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n,k;
int all[5001000];
int main()
{
    read(n);
    read(k);
    for(int i = 0;i<n;++i)
        read(all[i]);
    sort(all,all+n);
    printf("%d",all[k]);
}