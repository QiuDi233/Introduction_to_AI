/*描述
Sudoku is a very simple task. A square table with 9 rows and 9 columns is divided to 9 smaller squares 3x3 as shown on the Figure. 
In some of the cells are written decimal digits from 1 to 9. The other cells are empty. 
The goal is to fill the empty cells with decimal digits from 1 to 9, one digit per cell, in such way that in each row, 
in each column and in each marked 3x3 subsquare, all the digits from 1 to 9 to appear. Write a program to solve a given Sudoku-task. 

输入
The input data will start with the number of the test cases. For each test case, 9 lines follow, corresponding to the rows of the table.
On each line a string of exactly 9 decimal digits is given, corresponding to the cells in this line. If a cell is empty it is represented by 0.
输出
For each test case your program should print the solution in the same format as the input data.
The empty cells have to be filled according to the rules. If solutions is not unique, then the program may print any one of them.
样例输入
1
103000509
002109400
000704000
300502006
060000050
700803004
000401000
009205800
804000107
样例输出
143628579
572139468
986754231
391542786
468917352
725863914
237481695
619275843
854396127*/


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
