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
	//if(c==72&&map[nx+1][ny]=='#')go(-3,0);//�ϵ�ascllֵΪ73 
	if(c==75&&map[nx][ny-1]!='#'&&map[nx][ny-1]!='^'&&map[nx][ny-1]!='>'&&map[nx][ny-1]!='<'&&map[nx][ny-1]!='-')go(0,-1);//�� 
	if(c==77&&map[nx][ny+1]!='#'&&map[nx][ny+1]!='^'&&map[nx][ny+1]!='>'&&map[nx][ny+1]!='<'&&map[nx][ny+1]!='-')go(0,1);//�� 
	}
}
inline void print(){
	if(ifdied()) return;
	nowt=clock();
	score=(nowt-st)/1000;
	system("cls");
		for(int i=1;i<=20;i++){
		for(int j=1;j<=50;j++) putchar(map[i][j]);
		if(i==5) printf("@���������ڵ�λ��");
		if(i==6) printf("ֻ�в���#�Ų������ȥ");
		if(i==7) printf("��Ȼ���˶���Ҳ�ǻ�����");
		if(i==8) printf("---����ڲ���һ�����ʧ");
		if(i==10) printf("һ������^^^����Ϸ����");
		if(i==11) printf("�ȵ�<<<���ƶ������෽�������");
		if(i==12) printf("�ȵ�>>>���ƶ������෽�����ұ�"); 
		if(i==15) printf("�ٶȻ�������Ϸʱ��ӿ�");
		if(i==16) printf("ÿ������һ�룬��������1");
		if(i==17) printf("��ǰ�ٶ�%d ��ǰ����%d",speed,score);
		printf("\n");
	}
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
	return;
}
int con;
void game(){
	if(con==2){
		dif=1;
		printf("��ѡ��������ģʽ\n");
		printf("��Ϸ����1���ʼ��������׼��\n");
		Sleep(1000);	
	}
	else{
		dif=0;
		puts("��ѡ���˱�׼ģʽ");
		puts("��Ϸ����1���ʼ��������׼��");
		Sleep(1000); 
	}
	system("color 37");//����ɫ���� 
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
	puts("�������£�����ϸ�Ķ�");
	puts("����Ϸֻʹ��������Ҽ�����");
	puts("@���������ڵ�λ��");
	puts("ֻ�в���#�Ų������ȥ");
	puts("��Ȼ���˶���Ҳ�ǻ�����");
	puts("---����ڲ���һ�����ʧ");
	puts("һ������^^^����Ϸ����");
	puts("�ȵ�<<<���ƶ������෽�������");
	puts("�ȵ�>>>���ƶ������෽�����ұ�"); 
	puts("�ٶȻ�������Ϸʱ��ӿ�");
	puts("ÿ������һ�룬��������1");
	puts("����1��ʼ��Ϸ");
	puts("����2���������Ѷ�");
	puts("������ʾ�������Ѷȷǳ�����");
	scanf("%d",&con);
	while(con==1||con==2){  
		game();
		con=0;
		system("color 40");
		system("cls");
		puts("������\n����1�����׼ģʽ������2��������ģʽ������0����");
		printf("���η���%d\n",score);
		if(score>maxscore[dif]){
			puts("��ϲ�㣡�Ƽ�¼�ˣ�");
			printf("ԭ��¼��%d\n",maxscore[dif]);
			maxscore[dif]=score;
			outrk();
		}
		else if(maxscore[dif]-score<=10)
			puts("�ÿ�ϧ����һ����Ƽ�¼��");
		else puts("̫���ˣ����Ƽ�¼��Զ����!");
		printf("��ʷ��߷�����%d\n",maxscore[dif]);
		scanf("%d",&con);
		while(con!=1&&con!=0&&con!=2){
			puts("��ô�������أ���˵�˱�����������");
			puts("����1�����׼ģʽ,����2��������ģʽ,����0����,��������������");
			scanf("%d",&con);
		}
	}
	puts("�˳�");
	Sleep(2000);
	return 0;
}
