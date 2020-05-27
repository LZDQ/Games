#include<cstdio>
struct node{
	int map[9][9];
	int last_all;
	bool nonum[10][9][9];
	int last_h(int num,int x){
		int t=9;
		for(int i=0;i<9;i++) t-=nonum[num][x][i];
		return t;
	}
	int last_l(int num,int y){
		int t=9;
		for(int i=0;i<9;i++) t-=nonum[num][i][y];
		return t;
	}
	int last_g(int num,int g){
		int x=g/3*3,y=g%3*3,t=9;
		for(int i=x;i<x+3;i++)
			for(int j=y;j<y+3;j++)
				t-=nonum[num][i][j];
		return t;
	}
	void mknum(int x,int y,int num){
		last_all--;
		map[x][y]=num;
		for(int i=1;i<=9;i++)
			nonum[i][x][y]=1;
		for(int i=0;i<9;i++)
			nonum[num][x][i]=nonum[num][i][y]=1;
		for(int i=x/3*3;i<x/3*3+3;i++)
			for(int j=y/3*3;j<y/3*3+3;j++)
				nonum[num][i][j]=1;
		return ;
	}
	bool find_num(int num){
		bool mrk=0;
		for(int i=0;i<9;i++){
			if(last_h(num,i)==1)
				for(int j=0;j<9;j++)
					if(!nonum[num][i][j]){
						mknum(i,j,num);
						mrk=1;
					}
			if(last_l(num,i)==1)
				for(int j=0;j<9;j++)
					if(!nonum[num][j][i]){
						mknum(j,i,num);
						mrk=1;
					}
			if(last_g(num,i)==1){
				int x=i/3*3,y=i%3*3;
				for(int j=x;j<x+3;j++)
					for(int k=y;k<y+3;k++)
						if(!nonum[num][j][k]){
							mknum(j,k,num);
							mrk=1;
						}
			}
		}
		return mrk;
	}
	bool check(){
		int k;
		for(int i=1;i<=9;i++){
			for(int j=0;j<9;j++){
				if(last_h(i,j)==0){
					for(k=0;k<9;k++)
						if(map[j][k]==i) break;
					if(k==10) return 0;
				}
				if(last_l(i,j)==0){
					for(k=0;k<9;k++)
						if(map[k][j]==i) break;
					if(k==10) return 0;
				}
				if(last_g(i,j)==0){
					int x=j/3*3,y=j%3*3,nx,ny;
					for(nx=x;nx<x+3;nx++){
						for(ny=y;ny<y+3;ny++)
							if(map[nx][ny]==i) break;
						if(ny<y+3) break;
					}
					if(nx==x+3&&ny==y+3) return 0;
				}
			}
		}
		return 1;
	}
	void print(){
		printf("-------------------------\n");
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				if(j%3==0)	printf("| ");
				printf("%d ",map[i][j]);
			}
			printf("|\n");
			if(i%3==2) printf("-------------------------\n");
		}
		printf("\n\n\n\n");
		return ;
	}
};
node s;
bool dfs(node ges){  //guess
	for(int i=9;i>=1;i--)
		if(ges.find_num(i)) i=10;
	if(!ges.check()) return 0;
	if(ges.last_all==0){
		ges.print();
		return 1;
	}
	node t;
	for(int i=1;i<=9;i++)
		for(int j=0;j<9;j++)
			for(int k=0;k<9;k++)
				if(!ges.nonum[i][j][k]){
					t=ges;
					t.mknum(j,k,i);
					if(dfs(t)) return 1;
					else ges.nonum[i][j][k]=1;
				}
	return 0;
}
int main(){
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	s.last_all=81;
	int num;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			scanf("%1d",&num);
			if(num) s.mknum(i,j,num);
		}
	}
	if(!dfs(s)) printf("No solution!\n");
	return 0;
}
