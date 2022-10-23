#include <cstdio>
using namespace std;
int a,b,c;
int vis[10];
int nowa,nowb,nowc;
bool flag;
inline bool check()
{
	for(int i = 1;i<=9;++i)
		vis[i] = 0;
	for(int t = nowa;t;t/=10)
		if(vis[t%10])	return false;
		else vis[t%10] = 1;
	for(int t = nowb;t;t/=10)
		if(vis[t%10])	return false;
		else vis[t%10] = 1;
	for(int t = nowc;t;t/=10)
		if(vis[t%10])	return false;
		else vis[t%10] = 1;
	return true;
}
int main()
{
	scanf("%d%d%d",&a,&b,&c);
	//直接枚举第一个数就可以了
	for(int i = 1;i<=9;++i)
		for(int j = 1;j<=9;++j) 
			if(i != j)
				for(int k = 1;k<=9;++k)
					if(i != k && j != k)
					{
						nowa = i * 100 + j * 10 + k;
						if(nowa % a)	continue;
						nowb = nowa / a * b;
						nowc = nowa / a * c;
						if(check())	printf("%d %d %d\n",nowa,nowb,nowc),flag = true;
					}
	if(!flag)
		printf("No!!!");
	return 0;
}
