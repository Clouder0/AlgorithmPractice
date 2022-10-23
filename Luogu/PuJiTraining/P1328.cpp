#include <cstdio>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
const int maxn = 210;
int A[maxn],B[maxn];
int n,na,nb;
int all[5][5] =
{
    {0,0,1,1,0},
    {1,0,0,1,0},
    {0,1,0,0,1},
    {0,0,1,0,1},
    {1,1,0,0,0}
};
int main()
{
    read(n),read(na),read(nb);
    for(int i = 1;i<=na;++i)
        read(A[i]);
    for(int i = 1;i<=nb;++i)
        read(B[i]);
    int pa = 0,pb = 0,numa = 0,numb = 0;
    for(int i = 1;i<=n;++i)
    {
        ++pa,++pb;
        if(pa > na) pa = 1;
        if(pb > nb) pb = 1;
        int a = A[pa],b = B[pb];
        numa += all[a][b],numb += all[b][a];
    }
    printf("%d %d",numa,numb);
    return 0;
}