#include <cstdio>
#include <algorithm>
using namespace std;
int T,d,k;
inline bool in(int x,int y)
{
	return 1ll * x * x + 1ll * y * y <= 1ll * d * d;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d %d",&d,&k);
		int t;
		for(int i = 0;i<=d;++i)
		{
			if(in(k * i,k * i)) t = i;
			else break;
		}
		puts(in(k * t,k * t + k) ? "Ashish" : "Utkarsh");
	}
}
