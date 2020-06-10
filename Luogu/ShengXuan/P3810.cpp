#include <cstdio>
#include <algorithm>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 1e5 + 100;
struct node
{
    int a,b,c,cnt,ans;
}A[maxn],B[maxn];
int n,k,m;
bool cmp(const int &x,const int &y)
{
    if(A[x].a != A[y].a) return A[x].a < A[y].a;
    if(A[x].b != A[y].b) return A[x].b < A[y].b;
    return A[x].c < A[y].c;
}
void cdq(int l,int r)
{
    
}
int main()
{
    read(n),read(k);
    for(int i = 1;i<=n;++i) read(A[i].a),read(A[i].b),read(A[i].c);
    std::sort(A + 1,A + 1 + n,cmp);
    for(int i = 1,top = 0;i<=n;++i)
    {
        ++top;
        while(A[i].a != A[i+1].a && A[i].b != A[i+1].a && A[i].c != A[i+1].c)
        {
            ++m;
            B[m].a = A[i].a;
            B[m].b = A[i].b;
            B[m].c = A[i].c;
            B[m].cnt = top;
            top = 0;
        }
    }
    cdq(1,m);
    for(int i = 1;i<=m;++i)
    return 0;
}