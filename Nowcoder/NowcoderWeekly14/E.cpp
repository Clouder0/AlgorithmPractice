#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxm=1e6+5;
char s[maxm];
int nxt[maxm];
int vis[maxm];
int n;
void getnext(){
    int i=0;
    int j=nxt[0]=-1;
    while(i<n)  if(j==-1||s[i]==s[j]) i++,j++,nxt[i]=j; else j=nxt[j];
}
signed main(){
    scanf("%s",s);
    n=strlen(s);
    getnext();
    for(int i=1;i<n;i++) vis[nxt[i]]=1;
    int temp=nxt[n];
    while(temp>0){
        if(vis[temp])
        {
            for(int i=0;i<temp;i++) putchar(s[i]);
            return 0;
        }
        else temp=nxt[temp];
    }
    return 0;
}