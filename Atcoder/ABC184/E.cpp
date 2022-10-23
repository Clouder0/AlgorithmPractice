#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int maxn = 2100;
int n,m;
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
bool vis[maxn][maxn];
int d[maxn][maxn];
char s[maxn][maxn];
vector<pair<int,int> > V[200];
bool vvis[200];
int main()
{
	scanf("%d %d",&n,&m);
	int sx,sy,tx,ty;
	for(int i = 1;i<=n;++i) 
	{
		scanf("%s",s[i] + 1);
		for(int j = 1;j<=m;++j) 
		{
			if(s[i][j] == 'S') {sx = i,sy = j;continue;}
			if(s[i][j] == 'G') {tx = i,ty = j;continue;}
			if(s[i][j] != '.' && s[i][j] != '#') V[s[i][j]].push_back(make_pair(i,j));
		}
		
	}
	queue<pair<int,int> > q;
	q.push(make_pair(sx,sy)),vis[sx][sy] = 1;
	while(q.size())
	{
		int x = q.front().first,y = q.front().second;
		q.pop();
		if(vis[x][y] == 2) continue;
		vis[x][y] = 2;
		if(s[x][y] != '.' && s[x][y] != '#' && !vvis[s[x][y]])
		{
			vvis[s[x][y]] = 1;
			for(vector<pair<int,int> >::iterator it = V[s[x][y]].begin();it!=V[s[x][y]].end();++it)
				if(!vis[it->first][it->second]) vis[it->first][it->second] = 1,d[it->first][it->second] = d[x][y] + 1,q.push(make_pair(it->first,it->second));
		}
		for(int i = 0;i<4;++i)
		{
			int nx = x + dx[i],ny = y + dy[i];
			if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
			if(s[nx][ny] == '#') continue;
			if(!vis[nx][ny]) vis[nx][ny] = 1,d[nx][ny] = d[x][y] + 1,q.push(make_pair(nx,ny));
		}
	}
	if(vis[tx][ty]) printf("%d\n",d[tx][ty]);
	else puts("-1");
	return 0;
}
