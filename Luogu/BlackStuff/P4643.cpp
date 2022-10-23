#include <cstdio>
#include <algorithm>
int n,m,w[11000],res;
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1;i<=n;++i) scanf("%d",w + i),w[i] <<= 1;
	for(int i = 1,a,b,c;i<=m;++i) scanf("%d %d %d",&a,&b,&c),w[a] += c,w[b] += c;
	std::sort(w + 1,w + 1 + n);
	for(int i = n;i;--i) res += ((i & 1) ? -1 : 1) * w[i];
	return printf("%d\n",res >> 1),0;
}
