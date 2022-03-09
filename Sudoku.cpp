#include<iostream>
#include<cstring>
using namespace std;
int r[9][10];//第i行的j数出现的次数
int c[9][10];//第i列的j数出现的次数
int k[9][10];//第i个小框 j数出现的次数 
int sudoku[9][9];
int ans[9][9];
bool found=false;
void dfs(int x,int y){//给x y这个地方填数 先把行填好 再填列 
	if(sudoku[x][y]!=0){//这个地方不是空的 那就找下一个位置吧 
		if(y==8){
			dfs(x+1,0);
		}
		else{
			dfs(x,y+1);
		}
		return;
	}
	if(x==9&&y==0){
		for(int i=0;i<9;++i){
			for(int j=0;j<9;++j){
				ans[i][j]=sudoku[i][j];
			}
		}
		found=true;
		return;
	}
	int n=(x/3)*3+y/3;//在第n个小框 
	for(int i=1;i<=9;++i){//(x,y)处 每个数都试一试 
		if(found)
			return; 
		if(r[x][i]<1&&c[y][i]<1&&k[n][i]<1){
			r[x][i]++;
			c[y][i]++;
			k[n][i]++;
			sudoku[x][y]=i;
			if(y==8){
				dfs(x+1,0);
			}
			else{
				dfs(x,y+1);
			}
			r[x][i]--;
			c[y][i]--;
			k[n][i]--;//reverse
			sudoku[x][y]=0;
		}
	}
}
void input(){
	char ch;
	for(int i=0;i<9;++i){
		for(int j=0;j<9;++j){
			cin>>ch;
			//cin>>sudoku[i][j];
			sudoku[i][j]=ch-'0';
			r[i][sudoku[i][j]]++;
			c[j][sudoku[i][j]]++;
			int n=(i/3)*3+j/3;//在第n个小框 
			k[n][sudoku[i][j]]++; 
		}
	}
	return;
}
void output(){
	for(int i=0;i<9;++i){
		for(int j=0;j<9;++j){
			cout<<ans[i][j];
		}
		cout<<endl;
	}
	return;
} 
int main(){
	int T=0;
	cin>>T;
	while(T--){
		memset(r,0,sizeof(r));
		memset(c,0,sizeof(c));
		memset(k,0,sizeof(k));
		memset(sudoku,0,sizeof(sudoku));
		memset(ans,0,sizeof(ans));
		found=false;
		input();
		dfs(0,0);
		output();
	}
}
