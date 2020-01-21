#include <cstdio>
#include <random>
#include <ctime>
using namespace std;
int n,m,T,k;
long long temp;
mt19937 rnd(time(0));
inline int _abs(const int &x){return x>0?x:-x;}
inline int rd(int l,int r)
{
	return (_abs(rnd()) % (r-l+1)) + l;
}
int main()
{
    freopen("BingoGame1.in","w",stdout);
    //freopen("BingoGame1.out","w",stdout);
    n = 7;
    m = 4;
	T = 7;
	printf("%d %d %d\n",n,m,T);
	for(int i = 1;i<=n;putchar('\n'),++i)
		for(int j = 1;j<=m;++j)
			printf("%d ",rd(0,10000));
	
    for(int i = 1;i<=T;++i)
	{
		k = rd(10,100);
		printf("%d\n",k);
		for(int a = 1;a<=n;++a)
		{
			for(int b = 1;b<=m;++b)
				printf("%d ",rd(0,1));
			putchar('\n');
		}
		for(int j = 1;j<=k;++j)		
			printf("%d\n",rd(0,10000));
	}
    return 0;
}
