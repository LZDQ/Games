#include"opti.h"
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cstdlib>
const int 
chwhr[5][3]={{0,1,2},{0,1,3},{0,2,6},{0,2,5},{0,1,4}},
numwhr[5][4]={{3,4,5,6},{2,4,7,8},{1,5,13,14},{1,6,11,12},{2,3,9,10}};
int num[4];
int w[4],treenum[20];
char s[4],treech[20];
bool vis[4],isnum[20];
void print(int step){
	if(!isnum[step]){
		putchar('(');
		print((step<<1)+1);
		putchar(treech[step]);
		putchar(' ');
		print((step<<1)+2);
		putchar(')');
	}
	else printf("%d ",treenum[step]);
	return ;
}
double cnt(int step){
	if(isnum[step]) return treenum[step];
	char ch=treech[step];
	if(ch=='+') return cnt((step<<1)+1)+cnt((step<<1)+2);
	if(ch=='-') return cnt((step<<1)+1)-cnt((step<<1)+2);
	if(ch=='*') return cnt((step<<1)+1)*cnt((step<<1)+2);
	if(ch=='/') return cnt((step<<1)+1)/cnt((step<<1)+2);
}
bool dfsnum(int step){
	if(step==4){
		for(int i=0;i<5;i++){
			memset(isnum,0,20);
			for(int j=0;j<3;j++) treech[chwhr[i][j]]=s[j];
			for(int j=0;j<4;j++){
				treenum[numwhr[i][j]]=w[j];
				isnum[numwhr[i][j]]=1;
			}
			double t=cnt(0);
			if(fabs(t-24)<=1e-5) return 1;
		}
		return 0;
	}
	for(int i=0;i<4;i++)
		if(!vis[i]){
			w[step]=num[i];
			vis[i]=1;
			if(dfsnum(step+1)) return 1;
			vis[i]=0;
		}
	return 0;
}
bool dfsch(int step){
	if(step==3)
		return dfsnum(0);
	s[step]='+';
	if(dfsch(step+1)) return 1;
	s[step]='-';
	if(dfsch(step+1)) return 1;
	s[step]='*';
	if(dfsch(step+1)) return 1;
	s[step]='/';
	if(dfsch(step+1)) return 1;
	return 0;
}
int main(){
	system("cls");
	memset(vis,0,sizeof(vis));
	for(int i=0;i<4;i++){
		scanf("%d",num+i);
		if(num[i]==-1) return 0;
	}
	if(dfsch(0)){
		print(0);
		puts("");
	}
	else puts("No solution!");
	system("pause");
	main();
	return 0;
}
