#include <cstdio>
const int maxn = 100;
int n;
double totaldis,C,per;
double cost[maxn],dis[maxn];
double res = 1e18;
void dfs(int now,double totalcost,double nowhave)
{
	if(nowhave < 0) return;
	if(now == n) return (void)(res = res > totalcost ? totalcost : res);
	for(int i = now + 1;i<=n;++i)
	{
		double d = dis[i] - dis[now];
		if(cost[i] <= cost[now] && nowhave * per >= d) { dfs(i,totalcost,nowhave - d / per); return; }
	}
	//if no better choice can be reached without cost, then should choose one that is cheaper and tries to go there
	bool flag = 0;
	for(int i = now + 1;i<=n;++i) 
	{
		double d = dis[i] - dis[now];
		if(cost[i] <= cost[now])
		{
			double needoil = (d - nowhave * per) / per;
			if(nowhave + needoil > C) continue;
			double need = needoil * cost[now];
			dfs(i,totalcost + need,0);
			flag = 1;
		}
	}
	if(flag) return;
	//if no cheaper station, add here to full and tries to go.
	for(int i = now + 1;i<=n;++i)
	{
		double d = dis[i] - dis[now];
		if(cost[i] > cost[now])
		{
			double need = (C - nowhave) * cost[now];
			dfs(i,totalcost + need,C - d / per);
		}
		
	}
}
int main()
{
	scanf("%lf %lf %lf %lf %d",&totaldis,&C,&per,cost,&n);
	for(int i = 1;i<=n;++i) scanf("%lf %lf",dis + i,cost + i);
	cost[++n] = 0,dis[n] = totaldis;
	dfs(0,0,0);
	if(res < 1e18) printf("%.2f",res);
	else puts("No Solution");
	return 0;
}
