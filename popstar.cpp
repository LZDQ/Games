#include<cstdio>
#include<ctime>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<fstream>
#define reclose system
using namespace std;
const char COLOUR[]={' ','P','G','R','B','Y'};
const int GUESS=80;
const int DIRE[2][4]={{1,-1,0,0},{0,0,1,-1}};
const int SIZE=10;
const int SCORE[]={2000,1500,1200,1000,800,500,250,120,100};
int head,tail,qx[200],qy[200];
char s[100]="phusdown -s -";
int ans,rans;
int stkx[100],stky[100];
inline int popscore(int pop){
	return pop*pop*5;
}
inline int lastscore(int last){ //各种公式不同，请根据自己游戏版本调整
	if(last>=10) return 0;
	return SCORE[last];
}
struct node{
	/*

	y

A   |  1  1  4  3  3  2  1  1  2  1
9   |  2  5  5  3  4  3  4  2  1  1
8   |  1  1  1  2  2  4  4  4  3  1
7   |  1  2  2  2  3  5  3  2  2  4
6   |  1  3  1  1  1  5  3  3  3  4
5   |  4  1  2  2  2  1  1  1  2  3
4   |  3  1  5  5  5  3  1  4  2  3
3   |  1  3  3  2  4  2  2  2  2  1
2   |  2  2  3  5  2  1  1  1  2  1
1   |  1  1  3  3  4  2  2  3  1  1
	   _  _  _  _  _  _  _  _  _  _  x

	   1  2  3  4  5  6  7  8  9  A

	*/
	short map[SIZE+2][SIZE+2],top[SIZE+2];
	short nxt[SIZE+2],pre[SIZE+2];
	bool vis[SIZE+2][SIZE+2];
	int tot;
	int last;
	inline void print(bool x){
		puts(" -------------------- ");
		for(int i=SIZE;i>0;i--){
			putchar('|');
			int cnt=nxt[0]-1;
			for(int j=nxt[0];j<=SIZE;j=nxt[j]){
				if(x&&vis[j][i]) putchar('.');
				else if(top[j]>=i) putchar(COLOUR[map[j][i]]);
				else putchar(' ');
				putchar(' ');
				cnt+=nxt[j]-j-1;
			}
			for(int j=0;j<cnt;j++){
				putchar(' ');
				putchar(' ');
			}
			puts("|");
		}
		puts(" -------------------- \n\n\n");
		return ;
	}
	inline void init(){
		puts("\n请确认从文件in.txt读入\n");
		reclose("pause");
		s[0]='s';
		s[3]='t';
		last=SIZE*SIZE;
		s[strlen(s)]='f';
		s[strlen(s)]=' ';
		s[strlen(s)]='-';
		s[strlen(s)]='t';
		s[strlen(s)]=' ';
		s[strlen(s)]=49;
		s[strlen(s)]=48;
		s[strlen(s)]=48; //shutdown
		ifstream fin("in.txt");
		char ch;
		for(int i=SIZE;i>0;i--){
			for(int j=1;j<=SIZE;j++){
				fin>>ch;
				if(ch=='p'||ch=='P') map[j][i]=1;
				else if(ch=='g'||ch=='G') map[j][i]=2;
				else if(ch=='r'||ch=='R') map[j][i]=3;
				else if(ch=='b'||ch=='B') map[j][i]=4;
				else if(ch=='y'||ch=='Y') map[j][i]=5;
				else{
					puts("输入错误\n");
					printf("错误：x:%d y:%d\n\n\n",SIZE-i+1,j);
					printf("读入字符：\'%c\'\n\n",ch);
					puts("请退出并检查输入文本\n\n\n");
					while(1) reclose("pause");
				}
			}
			top[i]=SIZE;
			nxt[i]=i+1;
			pre[i]=i-1;
		}
		nxt[0]=1;
		pre[SIZE+1]=SIZE;
		puts("All right with input\n\n");
		puts("Have a good time!");
		for(int i=0;i<1e8;i++);
		puts("Please wait a moment");
		fin.close();
		return ;
	}
	inline void debug(){
		puts("debug");
		for(int i=nxt[0];i<=SIZE;i=nxt[i]){
			for(int j=1;j<=top[i];j++) putchar(COLOUR[map[i][j]]);
			printf(" %d top:%d\n",map[i][top[i]+1],top[i]);
		}
		puts("\n\n\n");
		return ;
	}
	void renew(){ //**********************
//		puts("renew");
		for(int i=nxt[0];i<=SIZE;i=nxt[i]){
			int tot=0;
			for(int j=1;j<=top[i];j++)
				if(!vis[i][j]) map[i][++tot]=map[i][j];
			top[i]=tot;
			if(top[i]==0){
				pre[nxt[i]]=pre[i];
				nxt[pre[i]]=nxt[i];
			}
		}
//		puts("finish renew");
		return ;
	}
	inline int getx(int x,int d){
		if(d==0) return nxt[x];
		if(d==1) return pre[x];
		return x;
	}
	inline int gety(int y,int d){
		return y+DIRE[1][d];
	}
}stk[100],pln[100],rpln[100];
int anstot,rtot;
int step;
bool bfs(node &a,node &t,int x,int y){
//	puts("\nstart bfs");
	memset(t.vis,0,sizeof(t.vis));
	head=0; tail=1;
	qx[1]=x; qy[1]=y;
	a.vis[x][y]=t.vis[x][y]=1;
	short clr=a.map[x][y];
//	printf("colour : %d\n",clr);
	while(head<tail){
		head++;
//		printf("head:%d tail:%d\n",head,tail);
		for(int i=0;i<4;i++){
			short nx=a.getx(qx[head],i);
			short ny=a.gety(qy[head],i);
//			printf("x:%d y:%d nx:%d ny:%d ",qx[head],qy[head],nx,ny);
//			printf("colour %c\n",COLOUR[a.map[nx][ny]]);
			if(ny<=a.top[nx]&&!t.vis[nx][ny]&&a.map[nx][ny]==clr){
//				puts("push");
				tail++;
				qx[tail]=nx;
				qy[tail]=ny;
				a.vis[nx][ny]=t.vis[nx][ny]=1;
			}
		}
	}
	t.last-=tail;
	t.tot+=popscore(tail);
//	t.debug();
//	t.renew();
//	puts("finish bfs\n\n");
//	reclose("pause");
	return tail>1;
}
long long dfscnt;
void dfs(node a){
	dfscnt++;
//	printf("%lld\n",dfscnt);
//	a.print(-1,-1);
//	reclose("pause");
	stk[++step]=a;
	memset(a.vis,0,sizeof(a.vis));
	bool mrk=0,les=(a.last<=25);
	for(int i=a.nxt[0];i<=SIZE;i=a.nxt[i]){
		while(!les&&rand()%100<=GUESS){
			i=a.nxt[i];
			if(i>SIZE) break;
		}
		if(i>SIZE) break;
		for(int j=1;j<=a.top[i];j+=1+(1-les)*rand()%10){
			node t=a;
			if(!a.vis[i][j]&&bfs(a,t,i,j)){
				mrk=1;
				stk[step]=t;
				t.renew();
				dfs(t);
			}
		}
	}
	if(!mrk&&ans<a.tot+lastscore(a.last)){
		ans=a.tot+lastscore(a.last);
		anstot=step;
		for(int i=1;i<=step;i++) pln[i]=stk[i];
	}
	step--;
//	puts("return");
	return ;
}
inline void tell(){
	puts("一共五种颜色:");
	puts("red r");
	puts("blue b");
	puts("green g");
	puts("purple p");
	puts("yellow y");
	puts("不区分大小写，每行末尾一个换行");
	puts("样例：");
	
	/*
	PBGPYPPGPP
	BBBYGBBBGB
	YBBRGYRYPY
	RPPYGGRBRR
	GPRBGGYRBR
	PGBGYYGBRG
	GPGRBRRYGR
	bgbbryybyb
	bpygrgpbpb
	bbrbrbrgbr    */
	
	puts("PBGPYPPGPP");
	puts("BBBYGBBBGB");
	puts("YBBRGYRYPY");
	puts("RPPYGGRBRR");
	puts("GPRBGGYRBR");
	puts("PGBGYYGBRG");
	puts("GPGRBRRYGR");
	puts("bgbbryybyb");
	puts("bpygrgpbpb");
	puts("bbrbrbrgbr\n");
	puts("输入格式：在相同目录下建立文本文档in.txt\n");
	puts("Have a good time!\n");
	return ;
}
node start;
int main(){
//	tell();
	puts("是否需要输入指南？");
	puts("如需要，请将程序第256行的注释去掉\n");
	reclose("pause");
	srand(time(NULL));
	start.init();
	puts("\n\n\n注意，由于程序使用随机数，求解时间不等，请耐心等待\n\n");
	puts("程序精髓在于第十行GUESS的值，GUESS在65~85之间效果不同\n");
	puts("GUESS越小，效率越低，但准确性强；GUESS越大则反之\n");
	puts("Calc 00%");
	for(int i=1;i<=10;i++){
		dfs(start);  //ans不用清零 
		if(rans<ans){
			rans=ans;
			rtot=anstot;
			for(int j=1;j<=rtot;j++) rpln[j]=pln[j];
		}
		printf("Calc %d",i*10);
		puts("%");
	}
	puts("\n\nFinish\n\n");
	for(int i=0;i<1e9;i++);
	puts("Please press enter to continue\n");
	puts("At last:");
	rpln[rtot].print(0);
	printf("\n\n\nsteps: %d\n",rtot);
	printf("\n\ntot: %d\n\n\n",rans);
	puts("\n如果对该结果不满意，请对程序第9行GUESS的值减少1~10\n\n");
	for(int i=1;i<rtot;i++){
		reclose("pause");
		printf("step %d:\n",i);
		rpln[i].print(1);
	}
	reclose("pause");
	rpln[rtot].print(0);
	printf("Over tot:%d\n\n",rans);
//	printf("Over dfs:%lld\n",dfscnt);
//	fclose(stdin);
//	fclose(stdout);
//	reclose("pause");
	return 0;
}
