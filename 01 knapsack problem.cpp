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
    int amount;//���~�`�ƶq
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
    input_file >> amount;//�`�@���X��object
    input_file >> capacity;//�e�q
    
    int max_profit=0;
    int current[amount];//current test case
    int solution[amount];
    item object[amount+1];
    
    object[0].weight = 0;//�����0��object�ŤU�ӡA���F����DP���B��
    object[0].value = 0;
    for(int a=1;a<=amount;a++){
        //read the input file
        input_file >> object[a].weight;
        input_file >> object[a].value;
    }

    //��l��table �����]��0
    vector<int> table[amount+1];//�إ�vector 

    for(a=0;a<=amount;a++){//a�O�ثe�b�ĴX��object
        for(b=0;b<=capacity;b++){//b�O��e�i�H�e�Ǫ��e�q
			if(a==0 || b==0){//��0�� 
				table[a].push_back(0);//a=0 �� b=0 ��0 
				continue;
			}
            
            if(object[a].weight<=b){//�i�H��o�U�A��n���n�զX
                if(table[a-1][b-object[a].weight] + object[a].value > table[a-1][b]){
                    table[a].push_back(table[a-1][b-object[a].weight] + object[a].value);
                }
                else{//���諸���p
                    table[a].push_back(table[a-1][b]);
                }
            }
            else{//�񤣤U�A��W���@�檺��
                table[a].push_back(table[a-1][b]);
            }
        }
    }

    cout<<"Ans:"<<table[amount][capacity]<<endl;

    vector<bool> ans;
    int col,row;//for calculate the result row:��� col:����
    col = amount;
    row = capacity;
    while(1){
    	if(col == 0 || row == 0){
     		break;
   		}
		
        if(table[col][row] > table[col-1][row]){//�W���������p�A����i�h
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

