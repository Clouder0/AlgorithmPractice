#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5 + 100;
int n,L[maxn],R[maxn];
int findL(int x){return L[x] == x ? x : L[x] = findL(L[x]);}
int findR(int x){return R[x] == x ? x : R[x] = findR(R[x]);}
char s[maxn];
inline void del(int x){L[x] = x - 1,R[x] = x + 1;}
int main()
{
	scanf("%d",&n);
	scanf("%s",s + 1);
	for(int i = 0;i<=n + 10;++i) L[i] = R[i] = i;
	int p1 = 1,p2 = 2,p3 = 3,res = 0;
	while(p3 <= n)
	{
		if(s[p1] == 'f' && s[p2] == 'o' && s[p3] == 'x')
		{
			del(p3),del(p2),del(p1),res += 3;
			for(int i = 1;i<=2;++i) if(p1) p1 = findL(p1 - 1);
			p2 = findR(p1 + 1),p3 = findR(p2 + 1);
			continue;
		}
		if(p3 >= n) break;
		p1 = findR(p1 + 1),p2 = findR(p2 + 1),p3 = findR(p3 + 1);
	}
	printf("%d\n",n - res);
	return 0;
}
