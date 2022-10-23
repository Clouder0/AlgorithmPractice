#include <cstdio>
#include <set>
#include <algorithm>
#include <cctype>
using namespace std;
const int bufSize = 1e6;
#define DEBUG
inline char nc()
{
	#ifdef DEBUG
	return getchar();
	#endif
	static char buf[bufSize],*p1,*p2;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,bufSize,stdin),p1==p2)?EOF:*p1++;
}
template<typename T>
inline T read(T &r)
{
	static char c;
	static int flag;
	r = 0,flag = 1;
	for(c = nc(); !isdigit(c); c = nc()) if(c == '-') flag = -1;
	for(;isdigit(c);c=nc()) r = r * 10 + c - 48;
	return r *= flag;
}
const int maxn = 1e5 + 100;
const int maxk = 18;
int n, m, h[maxn];
struct node
{
	int to;
	long long dis,adis,bdis;
}f[maxn][maxk][2];
template<typename T> inline T myabs(const T &x){return x > 0 ? x : -x;}
inline void ins(int i,pair<int,int> p)
{
	int d = myabs(h[i] - p.first),id = p.second;
	if(!f[i][0][1].to) f[i][0][1] = (node){id,d,0,d};
	else
	{
		if(f[i][0][1].dis > d || (f[i][0][1].dis == d && h[f[i][0][1].to] > h[id])) 
		{
			f[i][0][0] = (node){f[i][0][1].to,f[i][0][1].dis,f[i][0][1].dis,0};
			f[i][0][1] = (node){id,d,0,d};
		}
		else if(!f[i][0][0].to || (f[i][0][0].dis > d || (f[i][0][0].dis == d && h[f[i][0][0].to] > h[id]))) 
			f[i][0][0] = (node){id,d,d,0};
	}
}
int main()
{
	read(n);
	for(int i = 1;i <= n;++i) read(h[i]);
	set<pair<int,int> > S;
	for(int i = n;i;--i)
	{
		set<pair<int,int> >::iterator it = S.lower_bound(make_pair(h[i],0));
		if(it != S.end()) ins(i,*it);
		if(it != S.begin()) 
		{
			ins(i,*--it);
			if(it != S.begin()) ins(i,*--it),++it;
			++it;
		}
		if(it == S.end()) {S.insert(make_pair(h[i],i));continue;}
		++it;
		if(it != S.end()) ins(i,*it);
		else {S.insert(make_pair(h[i],i));continue;}
		++it;
		if(it != S.end()) ins(i,*it);
		else {S.insert(make_pair(h[i],i));continue;}
		S.insert(make_pair(h[i],i));
	}
	for(int j = 1;j<18;++j) 
		for(int i = 1; i <= n; ++i) 
		{
			node t1 = f[i][j-1][0];
			node t2 = f[t1.to][j-1][j == 1];
			//if(!t2.to) break;
			f[i][j][0] = (node){t2.to,t1.dis + t2.dis,t1.adis + t2.adis,t1.bdis + t2.bdis};
			t1 = f[i][j-1][1];
			t2 = f[t1.to][j-1][j != 1];
			f[i][j][1] = (node){t2.to,t1.dis + t2.dis,t1.adis + t2.adis,t1.bdis + t2.bdis};
		}
	int x0,anss = 0;
	read(x0);
	long long ansadis = 0,ansbdis = 0;
	for(int i = 1;i <= n;++i) 
	{
		int now = i,status = 0,left = x0,adis = 0,bdis = 0;
		for(int j = 17;j>=0;--j) 
			if(f[now][j][status].to && left >= f[now][j][status].dis) 
			{
				adis += f[now][j][status].adis,bdis += f[now][j][status].bdis;
				left -= f[now][j][status].dis,now = f[now][j][status].to;
			}	
		if(!anss) ansadis = adis,ansbdis = bdis,anss = i;
		else if(bdis == 0) 
		{
			if(ansbdis == 0 && h[i] > h[anss]) anss = i,ansadis = adis,ansbdis = bdis;
		}
		else if((adis * ansbdis < bdis * ansadis) || 
			(adis * ansbdis == bdis * ansadis && h[i] > h[anss])) 
				ansadis = adis,ansbdis = bdis,anss = i;
	}
	printf("%d\n",anss);
	read(m);
	while(m--)
	{
		static int now,x;
		read(now),read(x);
		long long adis = 0,bdis = 0;
		for(int j = 17;j>=0;--j) 
			if(f[now][j][0].to && x >= f[now][j][0].dis)
				adis += f[now][j][0].adis,bdis += f[now][j][0].bdis,
				x -= f[now][j][0].dis,now = f[now][j][0].to;
		printf("%lld %lld\n",adis,bdis);
	}
	return 0;
}
