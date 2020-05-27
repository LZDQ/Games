#include<conio.h>
#include<cstdio>
#include<windows.h>
#include<ctime>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstring>
using namespace std;
#define go(x,y) swap(map[nx][ny],map[nx+x][ny+y]),nx=nx+x,ny=ny+y
char map[100][100];
int maxscore[2];
int nx,ny;
int speed,score,downtime;
bool dif=0;
bool tool=0;
bool died=0;
int nowt;
int st;
int _a,_b;
int o=0;
bool ifdied(){
	if(nx==1||nx==20||map[nx+1][ny]=='^')return 1;
	return 0;
}
void up(){
	nx-=1;
	if(ifdied())return;
	if(speed>200)speed-=5;
	if(speed<300)downtime=100;
		for(int i=2;i<=19;i++){
		for(int j=2;j<=49;j++){
		if(i!=19)map[i][j]=map[i+1][j]; 
		if(i==19)map[i][j]=' ';
		}
	}
	if(o==0)return;
	int fh=rand()%2==0?1:-1;
	int mid=ny+fh*rand()%6;
	int df=rand()%15;
	if(dif==0) map[19][mid-1]=map[19][mid]=map[19][mid+1]='#';
	else map[19][mid-1]=map[19][mid]=map[19][mid+1]='-';
	if(df==0) map[19][mid-1]=map[19][mid]=map[19][mid+1]='^';
	if(df==5) map[19][mid-1]=map[19][mid]=map[19][mid+1]='>';
	if(df==10) map[19][mid-1]=map[19][mid]=map[19][mid+1]='<';
	if(df==12){
		if(dif==0) map[19][mid-1]=map[19][mid]=map[19][mid+1]='#';
		else map[19][mid-1]=map[19][mid]=map[19][mid+1]='-';
	}
}
inline void init(){
	st=clock();
	speed=1000,score=0,downtime=200;
	if(dif==1) speed-=200;
	memset(map,' ',sizeof(map));
	for(int i=1;i<=20;i++) map[i][1]=map[i][50]='#';
	for(int i=1;i<=50;i++) map[1][i]='#';
	int x,y;
	srand(time(NULL));
	x=5;
	y=25;
	map[x][y]='@';
	nx=x;
	ny=y;
	map[x+1][y-1]=map[x+1][y]=map[x+1][y+1]='#';
	return;
}
inline void down(){
	if(map[nx+1][ny]!='#'&&map[nx+1][ny]!='-'&&map[nx+1][ny]!='<'&&map[nx+1][ny]!='>'&&map[nx+1][ny]!='^') go(1,0);
	return ;
}
int na,nb;
void now(){
	if(ifdied()) return;
	nb=clock();
	if(nb-na>=downtime)down(),na=nb;
	while(map[nx+1][ny]=='<')go(0,-1);
	while(map[nx+1][ny]=='>')go(0,1);
	if(map[nx+1][ny]=='-'){
		if(_a!=0)_b=clock();
		if(_a==0)_a=clock();
		if(_b-_a>=1000)map[nx+1][ny]=' ',_a=_b=0;
	}
	if(map[nx+1][ny]!='-')_a=_b=0;
	int c;
	while(kbhit()!=0){
	c=_getch();
	//if(c==72&&map[nx+1][ny]=='#')go(-3,0);//上的ascll值为73 
	if(c==75&&map[nx][ny-1]!='#'&&map[nx][ny-1]!='^'&&map[nx][ny-1]!='>'&&map[nx][ny-1]!='<'&&map[nx][ny-1]!='-')go(0,-1);//左 
	if(c==77&&map[nx][ny+1]!='#'&&map[nx][ny+1]!='^'&&map[nx][ny+1]!='>'&&map[nx][ny+1]!='<'&&map[nx][ny+1]!='-')go(0,1);//右 
	}
}
inline void print(){
	if(ifdied()) return;
	nowt=clock();
	score=(nowt-st)/1000;
	system("cls");
		for(int i=1;i<=20;i++){
		for(int j=1;j<=50;j++) putchar(map[i][j]);
		if(i==5) printf("@代表你现在的位置");
		if(i==6) printf("只有踩着#才不会掉下去");
		if(i==7) printf("当然等了顶部也是会死的");
		if(i==8) printf("---块会在踩上一秒后消失");
		if(i==10) printf("一旦掉到^^^，游戏结束");
		if(i==11) printf("踩到<<<会移动到该类方块最左边");
		if(i==12) printf("踩到>>>会移动到该类方块最右边"); 
		if(i==15) printf("速度会随着游戏时间加快");
		if(i==16) printf("每多生存一秒，积分增加1");
		if(i==17) printf("当前速度%d 当前分数%d",speed,score);
		printf("\n");
	}
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
	return;
}
int con;
void game(){
	if(con==2){
		dif=1;
		printf("您选择了炼狱模式\n");
		printf("游戏将在1秒后开始，请做好准备\n");
		Sleep(1000);	
	}
	else{
		dif=0;
		puts("您选择了标准模式");
		puts("游戏将在1秒后开始，请做好准备");
		Sleep(1000); 
	}
	system("color 37");//蓝绿色背景 
	system("cls");
	init(); 
	int a=clock();
	int b;
	while(1){
		if(ifdied()) break;
		Sleep(128);
		now();  
		if(ifdied()) break;
		b=clock();
		if(b-a>=speed){
			o^=1;
			up();
			if(ifdied()) break;
			a=b;
		}
		print();
		if(ifdied()) break;
	}
	return;
}
inline void inrk(){
	ifstream rk("rk.txt");
	rk>>maxscore[0];
	rk>>maxscore[1];
	rk.close();
	return ;
}
inline void outrk(){
	ofstream rk("rk.txt");
	rk<<maxscore[0]<<endl;
	rk<<maxscore[1]<<endl;
	rk.close();
	return ;
}
int main(){
	inrk();
	puts("规则如下，请仔细阅读");
	puts("本游戏只使用左键和右键操作");
	puts("@代表你现在的位置");
	puts("只有踩着#才不会掉下去");
	puts("当然等了顶部也是会死的");
	puts("---块会在踩上一秒后消失");
	puts("一旦掉到^^^，游戏结束");
	puts("踩到<<<会移动到该类方块最左边");
	puts("踩到>>>会移动到该类方块最右边"); 
	puts("速度会随着游戏时间加快");
	puts("每多生存一秒，积分增加1");
	puts("输入1开始游戏");
	puts("输入2开启炼狱难度");
	puts("友情提示：炼狱难度非常恶心");
	scanf("%d",&con);
	while(con==1||con==2){  
		game();
		con=0;
		system("color 40");
		system("cls");
		puts("你死了\n输入1重玩标准模式，输入2重玩炼狱模式，输入0结束");
		printf("本次分数%d\n",score);
		if(score>maxscore[dif]){
			puts("恭喜你！破纪录了！");
			printf("原记录：%d\n",maxscore[dif]);
			maxscore[dif]=score;
			outrk();
		}
		else if(maxscore[dif]-score<=10)
			puts("好可惜，差一点就破记录了");
		else puts("太弱了，离破纪录还远着呢!");
		printf("历史最高分数：%d\n",maxscore[dif]);
		scanf("%d",&con);
		while(con!=1&&con!=0&&con!=2){
			puts("怎么不听话呢？都说了别输入其他数");
			puts("输入1重玩标准模式,输入2重玩炼狱模式,输入0结束,请勿输入其它数");
			scanf("%d",&con);
		}
	}
	puts("退出");
	Sleep(2000);
	return 0;
}
