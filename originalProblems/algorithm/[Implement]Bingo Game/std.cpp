#include <cstdio>
#include <cstring>
#include <map>
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
const int maxn = 210;
int n,m,T,k;
long long temp;
map<long long,pair<int,int> > mp;
int all[maxn][maxn];
int main()
{
    read(n);
    read(m);
    read(T);

    for(int i = 1;i<=n;++i)
        for(int j = 1;j<=m;++j)
            mp[read(temp)] = make_pair(i, j);

    while(T--)
    {
        int nums = 0,tot = 0;
        read(k);
        for(int i = 1;i<=n;++i)
            for(int j = 1;j<=m;++j)
                nums += read(all[i][j]);
        map<long long,pair<int,int> >::iterator it;
        pair<int,int> p;
        while(k--)
        {
            read(temp);
            if(tot == nums)
                continue;// if already Bingo,needn't judge it.
            it = mp.find(temp);
            if(it != mp.end())
            {
                p = it->second;
                if(all[p.first][p.second])
                {
                    all[p.first][p.second] = 0;
                    ++tot;
                }
            }
        }
        if(nums == tot)
            printf("Bingo!\n");
        else
            printf("No!\n");
    }
    return 0;
}
