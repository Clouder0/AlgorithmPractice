#include <cstdio>
#include <cstring>
using namespace std;
int c[2500];
int w[10] = {6,2,5,5,4,5,6,3,7,6};
int n,ans;
int main()
{
	memset(c,0x3f,sizeof(c));
	scanf("%d",&n);
	int temp;
	c[0] = 6;
	for(int i = 1;i<=1200;++i)
	{
		temp = 0;
		for(int j = i;j;j/=10)
			temp += w[j%10];
		c[i] = temp;
	}
	
	int ans = 0;
	for(int i = 0;i<=1200;++i)
		for(int j = 0;j<=1200;++j)
			if(c[i] + c[j] + c[i+j] == n - 4)
				++ans;
	printf("%d",ans);
	return 0;
}
