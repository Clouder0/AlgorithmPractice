#include <cstdio>
#include <cstring>
using namespace std;
long long sa[21][21][21];
long long w(int a,int b,int c)
{
	if(a <= 0 || b <= 0 || c <= 0)	return 1;
	if(a > 20 || b > 20 || c > 20)	return w(20,20,20);
	if(sa[a][b][c] != -1)	return sa[a][b][c];
	if(a < b && b < c)	return sa[a][b][c] = w(a,b,c-1)+w(a,b-1,c-1)-w(a,b-1,c);
	return sa[a][b][c] = w(a-1,b,c)+w(a-1,b-1,c)+w(a-1,b,c-1)-w(a-1,b-1,c-1);
}
int main()
{
	memset(sa,-1,sizeof(sa));
	//说次数多，直接记忆化呗
	int a,b,c;
	while(scanf("%d%d%d",&a,&b,&c)&&!(a == -1 && b == -1 && c == -1))
		printf("w(%d, %d, %d) = %lld\n",a,b,c,w(a,b,c));
	return 0;
}
