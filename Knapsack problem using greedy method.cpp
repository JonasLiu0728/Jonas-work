#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class item{
    public:
        double weight;
        double value;
        double cp;
        int serial;//record the original order
        int exist;//if this item is put into the bag
};

void output(item *A){
    cout<<"W:"<<A->weight<<" V:"<<A->value<<" C:"<<A->cp<<" S:"<<A->serial<<" E:"<<A->exist<<endl;
}

void swap(item *A , item *B){
    item temp;//暫存用的
    temp.weight = A->weight; 
    temp.value = A->value;
    temp.cp = A->cp;
    temp.serial = A->serial;

    A->weight = B->weight; 
    A->value = B->value;
    A->cp = B->cp;
    A->serial = B->serial;
    
    B->weight = temp.weight; 
    B->value = temp.value;
    B->cp = temp.cp;
    B->serial = temp.serial;
}

//calculate total permuation
int permutation(int a){
    int b = 1;
    for(int c=1;c<=a;c++){
        b = b*2;
    }
    return b;
}

int main(void){
    char b;
    int a;
    int amount;//物品總數量
    int capacity;
    string dataset;
    
    //read the item file
    cout<<"Enter the dataset:";
    cin>>dataset;
    string filename = "./dataset./"+ dataset + "./item.txt";//set the path
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
    int solution[amount] = {0};//initial solution (all zero)
    int permu = permutation(amount);//the total amount of permutation
    item object[amount];

    for(int a=0;a<amount;a++){
        //read the input file
        input_file >> object[a].weight;
        input_file >> object[a].value;
        object[a].cp = object[a].value / object[a].weight; 
        object[a].serial = a;
        object[a].exist = 0;//exist default to zero
    }

    //sort the data, from big to small
    //bubble sort
    for(int i=0;i<amount;i++){
        for(int b = 0;b<amount-i;b++){
            if(object[b].cp < object[b+1].cp){
                swap(object[b],object[b+1]);
            }
        }
    }
    for(int a=0;a<amount;a++){    
        if(object[a].weight <= capacity){//判斷是否放得進去
            object[a].exist = 1;//put it in the bag
            capacity -= object[a].weight;//調整剩下的容量
            max_profit += object[a].value;//改value
        }
    }

    //紀錄哪幾個是被挑中的
    for(int a=0;a<amount;a++){
        if(object[a].exist == 1){   
            solution[object[a].serial] = 1;
        }
    }
    cout<<"max profit:"<<max_profit<<endl; 
    for(int a=0;a<amount;a++){
        cout<<solution[a];
    }
       
}

