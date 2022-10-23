#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
char f[200][200];
int n,k;
char s[100000],s2[100000];
int main()
{
	f['R']['S'] = f['S']['R'] = 'R';
	f['P']['R'] = f['R']['P'] = 'P';
	f['S']['P'] = f['P']['S'] = 'S';
	f['R']['R'] = 'R';
	f['S']['S'] = 'S';
	f['P']['P'] = 'P';
	scanf("%d %d",&n,&k);
	scanf("%s",s + 1);
	for(int t = 1;t<=k;++t)
	{
		if(n & 1) {for(int i = 1;i<=n;++i) s[i+n] = s[i]; n <<= 1;}
		for(int i = 1;i <= n;i += 2) s2[(i + 1) >> 1] = f[s[i]][s[i+1]];
		n >>= 1;
		for(int i = 1;i<=n;++i) s[i] = s2[i];
	}
	putchar(s[1]);
	return 0;
}
