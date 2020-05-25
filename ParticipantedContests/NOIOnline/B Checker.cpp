#include <cstdio>
using namespace std;
template<typename T>
inline T read(T &r)
{
	static char c;r = 0;
	for(c = getchar();c>'9'||c<'0';c=getchar());
	for(;c<='9'&&c>='0';r=(r*10)+(c-48),c=getchar());
	return r;
}
const int maxn = 1e5 + 100;
int n,m;
int a[maxn];
int b[maxn];
int main()
{
	freopen("bubble.in","r",stdin);
	freopen("bubble.out","w",stdout);
	read(n);
	read(m);
	for(int i = 1;i<=n;++i)
		read(a[i]);
	int t,x;
	while(m--)
	{
		read(t);
		read(x);
		if(t == 1)
		{
			int temp = a[x];
			a[x] = a[x+1];
			a[x+1] = temp;
		}
		else
		{
			for(int i = 1;i<=n;++i)
				b[i] = a[i];
			for(int i = 1;i<=x;++i)
			{
				for(int j = 1;j<n;++j)
					if(b[j] > b[j+1])
					{
						int temp = b[j];
						b[j] = b[j+1];
						b[j+1] = temp;
					}
			}
			int ans = 0;
			for(int i = 1;i<=n;++i)
				for(int j = i-1;j;--j)
					if(b[i] < b[j])
						++ans;
			printf("%d\n",ans);
		}
	}
	return 0;
}
