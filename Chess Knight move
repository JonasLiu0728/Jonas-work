/*
劉期正 B103040023
日期:2020/10/9
用途:計算西洋棋騎士的走法 ，並用遞迴方法 
*/

#include<iostream>
#include<cstdlib>
#include<iomanip> 
using namespace std;

//方向的變化 
int dirx[9]={0,-2,-1,1,2,2,1,-1,-2};//將方向1~8所對英相加的數量存在陣列,比較方便+- 
int diry[9]={0,1,2,2,1,-1,-2,-2,-1};

int array[10][10];//要output的陣列， 

bool out_range(int x,int y ,int &tempx,int &tempy, int move){//測試是否超出邊界 
	if(array[x+dirx[move]][y+diry[move]] == 0 ){
		//設定temp，等等moving函示會用到 
		tempx = dirx[move];
		tempy = diry[move];
		return 1;//可以走 
	}
	else{
		return 0;//沒辦法走 
	}	
}
/*
n:陣列的大小 
x,y 現在的位置
tempx,tempy:將要改變的位置
move:移動的位置
step:現在走到第幾步 
*/
int moving(int size,int x,int y,int step){
	int a;
	int tempx,tempy,next;
	if(step > size*size){//滿了 
		return 1;
	}
	else{//沒有滿，開始測試方向 
		for(a=1;a<8;a++){
			if(out_range(x,y,tempx,tempy,a))//確定這個方向可以走 
			{
				array[x+tempx][y+tempy] = step;
				//往下一步走，recursion的部分
				next = moving(size,x+tempx,y+tempy,step+1);
				
				if(next == 0){//繼續往下一步走，發現不能走 
					array[x+tempx][y+tempy] = 0;//之前寫上去的改回0 
					continue;
				}  
				else if(next == 1){
					return 1;
				}
			}
		}
	}
	return 0;//真的完全走不了的話，第一個recursion會==0，在主函示裡面就知道無解 
}

int main(void){
	int step,x,y;
	int a,b,c;//controller
	for(a=1;a<7;a++){
		x=2;//第一個位置在2,2 
		y=2;
		step = 1;//第一步 
		//把邊界外的陣列內容設為-1 
		cout<<"n="<<a<<endl;
		for(b=0;b<a+4;b++){
			for(c=0;c<a+4;c++){
				if(b<2 | b>1+a | c<2 | c>1+a){
					array[b][c] = -1;
				}
				else{
					array[b][c]=0;
				}
			}
		}
		
		array[2][2] = 1;
		step++;//走完第一步了
		
		if(moving(a,x,y,step)){
			for(b=2;b<2+a;b++){
				for(c=2;c<2+a;c++){
					cout<<setw(3)<<array[b][c];
				}
				cout<<endl;
			}
		} 
		else{
			cout<<"no solution"<<endl;
		}
	}
}





