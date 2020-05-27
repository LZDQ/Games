#include<cstdio>
#include<ctime>
#include<cstring>
#include<cstdlib>
#define reclose system
using namespace std;
const char COLOUR[]={' ','P','G','R','B','Y'};
const int DIRE[2][4]={{1,-1,0,0},{0,0,1,-1}};
const int SIZE=10;
const int SCORE[]={2000,1500,1200,1000,800,500,250,120,100};
int head,tail,qx[200],qy[200];
char s[100]="phusdown -s -";
int ans;
int stkx[100],stky[100];
int px[100],py[100],anstot;
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
    inline void print(int x,int y){
        puts(" -------------------- ");
        for(int i=SIZE;i>0;i--){
            putchar('|');
            int cnt=nxt[0]-1;
            for(int j=nxt[0];j<=SIZE;j=nxt[j]){
                if(j==x&&i==y) putchar('.');
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
    inline void scan(){
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
        char ch;
        for(int i=SIZE;i>0;i--){
            for(int j=1;j<=SIZE;j++){
                ch=getc(stdin);
                if(ch=='p'||ch=='P') map[j][i]=1;
                else if(ch=='g'||ch=='G') map[j][i]=2;
                else if(ch=='r'||ch=='R') map[j][i]=3;
                else if(ch=='b'||ch=='B') map[j][i]=4;
                else if(ch=='y'||ch=='Y') map[j][i]=5;
                else ;//reclose(s);
            }
            if(getc(stdin)!='\n') ;//reclose(s);
            top[i]=SIZE;
            nxt[i]=i+1;
            pre[i]=i-1;
        }
        nxt[0]=1;
        pre[SIZE+1]=SIZE;
        puts("All right with input\n\nHave a good time!");
        for(int i=0;i<1e8;i++);
        puts("Please wait a moment");
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
//      puts("renew");
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
//      puts("finish renew");
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
}stk[100],pln[100];
int step;
bool bfs(node &a,node &t,int x,int y){
//  puts("\nstart bfs");
    memset(t.vis,0,sizeof(t.vis));
    head=0; tail=1;
    qx[1]=x; qy[1]=y;
    a.vis[x][y]=t.vis[x][y]=1;
    short clr=a.map[x][y];
//  printf("colour : %d\n",clr);
    while(head<tail){
        head++;
//      printf("head:%d tail:%d\n",head,tail);
        for(int i=0;i<4;i++){
            short nx=a.getx(qx[head],i);
            short ny=a.gety(qy[head],i);
//          printf("x:%d y:%d nx:%d ny:%d ",qx[head],qy[head],nx,ny);
//          printf("colour %c\n",COLOUR[a.map[nx][ny]]);
            if(ny<=a.top[nx]&&!t.vis[nx][ny]&&a.map[nx][ny]==clr){
//              puts("push");
                tail++;
                qx[tail]=nx;
                qy[tail]=ny;
                a.vis[nx][ny]=t.vis[nx][ny]=1;
            }
        }
    }
    t.last-=tail;
    t.tot+=popscore(tail);
//  t.debug();
    t.renew();
//  puts("finish bfs\n\n");
//  reclose("pause");
    return tail>1;
}
long long dfscnt;
void dfs(node a){
    dfscnt++;
//  printf("%lld\n",dfscnt);
//  a.print(-1,-1);
//  reclose("pause");
    memset(a.vis,0,sizeof(a.vis));
    stk[++step]=a;
    bool mrk=0,les=(a.last<=25);
    for(int i=a.nxt[0];i<=SIZE;i=a.nxt[i]){
        while(!les&&rand()%100<=80){
            i=a.nxt[i];
            if(i>SIZE) break;
        }
        if(i>SIZE) break;
        for(int j=1;j<=a.top[i];j+=(les?1:rand()%10+1)){
            node t=a;
            if(!a.vis[i][j]&&bfs(a,t,i,j)){
                mrk=1;
                stkx[step]=i;
                stky[step]=j;
                dfs(t);
            }
        }
    }
    if(!mrk&&ans<a.tot+lastscore(a.last)){
        ans=a.tot+lastscore(a.last);
        anstot=step;
        for(int i=1;i<=step;i++){
            pln[i]=stk[i];
            px[i]=stkx[i];
            py[i]=stky[i];
        }
    }
    step--;
//  puts("return");
    return ;
}
node start;
int main(){
//  freopen("in.txt","r",stdin);
//  freopen("out.txt","w",stdout);
    srand(time(NULL));
    start.scan();
    dfs(start);
    puts("\n\nAll right\n\n");
    puts("Please press enter to continue\n");
    printf("step: %d\n\n\n",anstot);
    printf("\n\nOver tot:%d\n\n",ans);
    for(int i=1;i<anstot;i++){
        printf("step %d:\n",i);
//      reclose("pause");
        pln[i].print(px[i],py[i]);
    }
    pln[anstot].print(0,0);
//  printf("Over dfs:%lld\n",dfscnt);
//  fclose(stdin);
//  fclose(stdout);
//  reclose("pause");
    return 0;
}
