#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class item{
    public:
        int weight;
        int value;
};

//calculate total permuation
int permutation(int a){
    int b = 1;
    for(int c=1;c<=a;c++){
        b = b*2;
    }
    return b;
}

int main(void){
    int a;
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
    input_file >> amount;
    input_file >> capacity;
    
    int max_profit=0;
    int current[amount];//current test case
    int solution[amount];
    int permu = permutation(amount);//the total amount of permutation
    item object[amount];

    for(int a=0;a<amount;a++){
        //read the input file
        input_file >> object[a].weight;
        input_file >> object[a].value;
        //cout<<"object weight:"<<object[a].weight<<" object value:"<<object[a].value<<endl;
    }


    for(int a=1; a<=permu-1 ; a++)
    {
        //CREATE PERMUTATION
        int temp; int b = amount-1; int c = a;//c represent for a
        for(int a =0;a<amount;a++){
            current[a]=0;//陣列的值先設為0 
        }
        while(c>0){
            temp = c%2;//從最後一位開始取
            current[b] = temp;
            c = c/2;
            b--;//move to the upper digit
        }

        //create temperarily variable
        int t_profit=0;//temp profit
        int t_weight=0;
        for(int a=0;a<amount;a++){
            if(current[a]==1){//要放進去
                t_weight += object[a].weight;
                t_profit += object[a].value;
            }
            if(t_weight > capacity) t_profit = 0;
        }
        //cout<<"t_weight:"<<t_weight<<" t_profit:"<<t_profit<<endl;
        if(t_weight <= capacity){//裝得下
            if(t_profit > max_profit){//有更佳解
                max_profit = t_profit;
                for(int b=0;b<amount;b++){
                    solution[b] = current[b];
                }
            }


        }
    }
    cout<<"Max profit:"<<max_profit<<endl;
    cout<<"solution:";
    for(int b=0;b<amount;b++){
         cout<<solution[b]<<"";
    }
    cout<<endl;

    return 0;
}

