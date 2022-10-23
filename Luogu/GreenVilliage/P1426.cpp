#include <cstdio>
using namespace std;
int s,x;
double speed = 7.0;
double pos;
int main()
{
	scanf("%d%d",&s,&x);
	//由于数据无敌小，直接包里模拟
	//if(s - x < 0 && s + x >= 7){printf("y");return 0;}
	for(int i = 0;i<=1000;++i) 
	{
		if(pos >= s - x && pos <= s + x)
		{
			if(pos + speed > s + x)	printf("n");
			else printf("y");
			return 0;
		}
		pos += speed;
		speed *= 0.98;
	}
	printf("n");
	return 0;
}
