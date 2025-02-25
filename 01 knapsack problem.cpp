#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class item{
    public:
        int weight;
        int value;
};

int max(int a,int b){
    if(a>=b) return a;
    return b;
}

int main(void){
    int a,b;
    int amount;//物品總數量
    int capacity;
    string dataset;
    
    //read the item file
    cout<<"Enter the dataset:";
    cin>>dataset;
    string filename = "./dataset./"+ dataset + "./item.txt";
    ifstream input_file(filename.c_str());
    if (!input_file.is_open()) {

        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }

    //start reading variables
    input_file >> amount;//總共有幾個object
    input_file >> capacity;//容量
    
    int max_profit=0;
    int current[amount];//current test case
    int solution[amount];
    item object[amount+1];
    
    object[0].weight = 0;//先把第0個object空下來，為了之後DP填表運用
    object[0].value = 0;
    for(int a=1;a<=amount;a++){
        //read the input file
        input_file >> object[a].weight;
        input_file >> object[a].value;
    }

    //初始化table 全部設成0
    vector<int> table[amount+1];//建立vector 

    for(a=0;a<=amount;a++){//a是目前在第幾個object
        for(b=0;b<=capacity;b++){//b是當前可以容納的容量
			if(a==0 || b==0){//第0行 
				table[a].push_back(0);//a=0 或 b=0 接0 
				continue;
			}
            
            if(object[a].weight<=b){//可以放得下，選要不要組合
                if(table[a-1][b-object[a].weight] + object[a].value > table[a-1][b]){
                    table[a].push_back(table[a-1][b-object[a].weight] + object[a].value);
                }
                else{//不選的情況
                    table[a].push_back(table[a-1][b]);
                }
            }
            else{//放不下，放上面一格的值
                table[a].push_back(table[a-1][b]);
            }
        }
    }

    cout<<"Ans:"<<table[amount][capacity]<<endl;

    vector<bool> ans;
    int col,row;//for calculate the result row:橫排 col:直排
    col = amount;
    row = capacity;
    while(1){
    	if(col == 0 || row == 0){
     		break;
   		}
		
        if(table[col][row] > table[col-1][row]){//上面那格比較小，有放進去
            ans.push_back(1);
            row -= object[col].weight;
            col--;//modify the column
            continue;
        }
        else{
            ans.push_back(0);
            col--;
            continue;
        }     
    }
    
    cout<<"Solution:";
	for(int a=amount-1;a>=0;a--){
        cout<<ans[a];
    }
    return 0;
}


//dt03 : Ans:13549094

