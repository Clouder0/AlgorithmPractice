#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int N=100100;
int n,f[N][16],dis[20][20];
char s[N];
int q[N],d[N];
int mark[N];
int c[N][1<<8];
inline void bfs(int c){
    int l=0,r=0;
    for(int i=1;i<=n;i++)if(s[i]-'a'==c){
        q[r++]=i,d[i]=0;
    }else   d[i]=-1;
    bool vis[16]={0};
    vis[c]=true;
    while(l<r){
        int now=q[l++];
        if(!vis[s[now]-'a']){
            vis[s[now]-'a']=true;
            for(int i=1;i<=n;i++)
                if(s[i]==s[now]&&d[i]==-1){
                    d[i]=d[now]+1;
                    q[r++]=i;
                }
        }
        if(now>1&&d[now-1]==-1) q[r++]=now-1,d[now-1]=d[now]+1;
        if(now<n&&d[now+1]==-1) q[r++]=now+1,d[now+1]=d[now]+1;
    }
    for(int i=1;i<=n;i++)
        if(d[i]!=-1)f[i][c]=d[i];
}
int main(){
   // freopen("1.out","w",stdout);
    scanf("%d",&n);
    scanf("%s",s+1);
    memset(f,0x3f,sizeof(f));
    for(int i=0;i<8;i++)
        bfs(i);
    memset(dis,0x3f,sizeof(dis));
    for(int i=1;i<=n;i++)
        for(int j=0;j<8;j++)
            dis[s[i]-'a'][j]=min(dis[s[i]-'a'][j],f[i][j]);
    for(int i=1;i<=n;i++)   for(int j=0;j<8;j++)
        if(f[i][j]>dis[s[i]-'a'][j])    mark[i]|=1<<j;
   // for(int i=1;i<=n;i++)
   //     printf("mark[%d]=%d\n",i,mark[i]);
    int ans=0;
    long long cnt=0;
    for(int i=1;i<=n;i++){
        for(int j=max(i-15,1);j<i;j++){
            int now=i-j;
            for(int k=0;k<8;k++)
                now=min(now,f[j][k]+1+f[i][k]);
            if(now==ans)    cnt++;
            if(now>ans)     ans=now,cnt=1;    
        }
        int t=i-16;
        if(t>=1)    c[s[t]-'a'][mark[t]]++;
        for(int j=0;j<8;j++)    for(int k=0;k<256;k++)
            if(c[j][k]){
                int now=0x7fffffff;
                for(int l=0;l<8;l++){
                    now=min(now,dis[j][l]+1+f[i][l]+((k&(1<<l))>>l));
                   //printf("%d\n",(k&(1<<l))>>l);
                }
                if(now==ans)    cnt+=c[j][k];
                if(now>ans) ans=now,cnt=c[j][k];
            }
    }
    printf("%d %lld\n",ans,cnt);
}