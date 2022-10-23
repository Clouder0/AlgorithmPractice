#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 5100;
int x0,a,b,c,d;
int n,m,q;
int T[maxn * maxn], P[maxn * maxn];
int L[maxn],R[maxn];
int main()
{
	scanf("%d %d %d %d %d",&x0,&a,&b,&c,&d);
	scanf("%d %d %d",&n,&m,&q);
	for(int i = 1;i<=n*m;++i) x0 = (1ll * a * x0 * x0 + 1ll * b * x0 + c) % d,T[i] = i,std::swap(T[i],T[x0 % i + 1]);
	//for(int i = 1;i<=n*m;++i) T[i] = i,std::swap(T[i],T[x[i] % i + 1]);
	for(int i = 1,a,b;i<=q;++i) scanf("%d %d",&a,&b),std::swap(T[a],T[b]);
	for(int i = 1;i<=n*m;++i) P[T[i]] = i;
	for(int i = 1;i<=n;++i) L[i] = 1,R[i] = m;
	printf("1 ");
	int p = P[1];
	int x = (p + m - 1) / m;
	int y = p - m * (x - 1);
	for(int i = x-1;i>0;--i) R[i] = std::min(R[i],y);
	for(int i = x+1;i<=n;++i) L[i] = std::max(L[i],y);
	for(int i = 2;i <= n * m;++i) 
	{
		p = P[i];
		x = (p + m - 1) / m;
		y = p - m * (x - 1);
		if(y >= L[x] && y <= R[x]) 
		{
			//printf("%d %d %d\n",i,L[pos[i].first],R[pos[i].first]);
			printf("%d ",i);
			for(int i = x-1;i>0;--i) R[i] = std::min(R[i],y);
			for(int i = x+1;i<=n;++i) L[i] = std::max(L[i],y);
		}
	}
	return 0;
}
