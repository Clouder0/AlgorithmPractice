#include <cstdio>
using namespace std;
inline char nc()
{
	static char buf[1000000],*p1 = buf,*p2 = buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline T read(T &r)
{
    static char c;static int flag;r=0,flag = 1;
    for(c=nc();c>'9'||c<'0';c=nc()) if(c == '-')	flag = -1;
    for(;c>='0'&&c<='9';r=(r<<1)+(r<<3)+(c^48),c=nc());
    return r*=flag;
}
int n,m,T,k;
long long temp;
long long all[210][210];
bool used[210][210];
int main()
{
    read(n);
    read(m);
    read(T);
    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=m;++j)
            read(all[i][j]);
    while(T--)
    {
        read(k);
        for(int i = 1;i<=n;++i)
            for(int j = 1;j<=m;++j)
                read(used[i][j]);
        while(k--)
        {
            read(temp);
            for(int i = 1;i<=n;++i)
                for(int j = 1;j<=m;++j)
                    if(used[i][j] && temp == all[i][j])
                        used[i][j] = false;
        }
        for(int i = 1;i<=n;++i)
            for(int j = 1;j<=m;++j)
                if(used[i][j])
                {
                    printf("No!\n");
                    goto end;
                }
        printf("Bingo!\n");
        end:;
    }
    return 0;
}
