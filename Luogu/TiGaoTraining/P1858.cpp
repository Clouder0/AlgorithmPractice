#include <cstdio>
#include <algorithm>
#include <cstring>
template<typename T>
void read(T &r)
{
    static char c;r=0;
    for(c=getchar();c>'9'||c<'0';c=getchar());
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=getchar());
}
int n,m,k;
int V[210],W[210];
int f[5100][60];
int temp[60];
int main()
{
    memset(f,~0x3f,sizeof(f));
    f[0][1] = 0;
    read(n),read(m),read(k);
    for(int i = 1;i<=k;++i) read(W[i]),read(V[i]);
    for(int i = 1;i<=k;++i)
    {
        for(int j = m;j>=W[i];--j)
        {
            int p = 1,q = 1,y = 1;
            while(y <= n)
            {
                if(f[j][p] > f[j - W[i]][q] + V[i]) temp[y++] = f[j][p++];
                else temp[y++] = f[j - W[i]][q++] + V[i];
            }
            for(int b = 1;b<=n;++b) f[j][b] = temp[b];
        }
    }
    int sum = 0;
    for(int i = 1;i<=n;++i) sum += f[m][i];
    printf("%d",sum);
    return 0;
}