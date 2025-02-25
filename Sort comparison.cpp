//B103040023 劉期正
//撰寫日期:2022/11/21
//測試5種排序法的執行效率 
#include<iostream>
#include<cstdlib> 
#include<ctime>
//cout<<double(b)/CLOCKS_PER_SEC<<endl; 
#include<algorithm>
#include<fstream>
//insertion sort / merge sort / quick sort 自己寫
//selection sort / radix sort 可直接call 
using namespace std;
int size;//要sort的陣列的長度
int q,a,b;//計算次數用的 
int array[500000];
int cal[500000];
void output(int A[],int size);

//insertion sort
void insertion_sort(int A[],int size)
{
	int a,b;
	for(a=1;a<size;a++)
	{
		int temp = A[a];//要拿來比較的數 
		for(b=a-1;b>=0;b--)
		{
			if(A[b] > temp)//比較大 順序是正確的 因此不是插在這邊 
			{
				A[b+1] = A[b];//往後移一格 
				A[b] = temp;
			}
			else if(A[b] < temp)//下一個比較的比temp小了，因此是要插在這個數的下一個 
			{
				A[b+1] = temp;
				break; 
			}	
		}
	}
}
// merge sort
/*
p:左邊邊界 
q:右邊邊界 
m:中間數 
*/
void Merge_Sort(int A[], int p, int q);
void Merge(int A[], int p, int q, int m);
void merge_sort(int A[], int p, int q) {
    if (p < q) {
        int m = (p + q) / 2;//從中間切開 
        merge_sort(A, p, m);      // 遞迴排序子陣列 A[p...m]
        merge_sort(A, m + 1, q);  // 遞迴排序子陣列 A[m+1...q]
        Merge(A, p, q, m);  // 將左右兩個以排序好的子陣列合併
    }
}
//merge 是把一個陣列切開再合起來 
void Merge(int A[], int p, int q, int m) {
    int n1 = m - p + 1;  // 新的左邊的陣列的長度
    int n2 = q - m;      // 新的右邊的陣列的長度
    /*Let L[0...n1] and R[0...n2] be new arrays
    and copy A[p...m] to L[0...n1]
    and copy A[m+1...q] to R[0...n2] */
    // 創建新的陣列
    int L[n1];
    int R[n2];
    // 賦值
    for (int i = 0; i < n1; i++) {//左邊那半邊的陣列 
        L[i] = A[p + i];
    }
    for (int i = 0; i < n2; i++) {//右邊那半邊的陣列 
        R[i] = A[i + m + 1];
    }
    int i = 0, j = 0;
 
    for (int k = p; k <= q; k++) {
        if (i >= n1) {
            A[k] = R[j];
            j++;
        } else if (j >= n2) {
            A[k] = L[i];
            i++;
        } else if (L[i] <= R[j]) {  // 左邊比較小，左邊放回A
            A[k] = L[i];
            i++;
        } else {  // 右邊比較小，那就放右邊
            A[k] = R[j];
            j++;
        }
    }
}
//自行撰寫quick sort


void quick_sort(int* A,const int left,const int right)
{
	if(left < right)//當左邊不大於右邊 
	{
		int i = left;
		int j = right+1;
		int pivot = A[left];//最左邊的那個資料當pivot，用來比較用的 
		do
		{
			do
			{
				i++;//向右找一個 
			}while(A[i]<pivot);
		
			do
			{
				j--;//向左找一個 
			}while(A[j]>pivot);
		
			if(i<j) swap(A[i],A[j]);//交換兩個順序不對的 
		}while(i < j);
		swap(A[left],A[j]);//換pivot 
		//分成兩邊 繼續做quick sort 
		quick_sort(A,left,j-1);
		quick_sort(A,j+1,right);
	}
	
} 

//內建qsort
int compare(const void* a,const void* b) 							//qSort需要的函式 來源:網路 
{
	int temp=*(int*)(a)-*(int*)(b);
	if(temp>0) return 1;
	else if (temp<0) return -1;
	else return 0;
} 
//輸出 
void output(int A[],int size){
	for(int a = 0;a<size;a++){
		cout<<A[a]<<endl;
	}
}
//賦值
void assign(int A[],int B[],int size)//assign a to b
{
	int a;
	for(a=0;a<size;a++)
	{
		B[a] = A[a];
	}
}  

int main(void){
	clock_t j,k;
	//計算時間的double 
	long double insertion_sort_time=0;
	double merge_sort_time=0;
	double quick_sort_time=0;
	double qsort_time=0;
	double sort_time=0;
	//開啟input檔案 
	ifstream input;
	input.open("input.txt");
	input>>size;
	//output stream 
	ofstream outputA;
	ofstream outputB;
	ofstream outputC;
	ofstream outputD;
	ofstream outputE;
	//open the files
	outputA.open("outputA.txt",ios::out);
	outputB.open("outputB.txt",ios::out);
	outputC.open("outputC.txt",ios::out);
	outputD.open("outputD.txt",ios::out);
	outputE.open("outputE.txt",ios::out);
	outputA<<"Insertion sort"<<endl;
	outputB<<"Merge sort"<<endl;
	outputC<<"Quick sort"<<endl;
	outputD<<"內建 qsort"<<endl;
	outputE<<"內建sort"<<endl;
	//cout<<"size:"<<size<<endl;
	for(q=0;q<10;q++){
		for(a=0;a<size;a++){
			int temp;
			input>>temp;
			array[a] = temp;				//array[a] = input_stream[a];
		}
		
		//insertion sort
		assign(array,cal,size);
		j=clock();
		insertion_sort(cal,size);
		k=clock();
		insertion_sort_time += k-j;
		for(a=0;a<size;a++)
		{
			outputA<<cal[a]<<endl;
		}
		
		//merge sort
		assign(array,cal,size);
		j=clock();
		merge_sort(cal,0,size);
		k=clock();
		merge_sort_time += k-j;
		for(a=0;a<size;a++)
		{
			outputB<<cal[a]<<endl;
		}
		
		
		//quick sort
		assign(array,cal,size);
		j=clock();
		quick_sort(cal,0,size);
		k=clock();
		quick_sort_time += k-j;
		for(a=0;a<size;a++)
		{	
			outputC<<cal[a]<<endl;
		}
		
		//內建quick sort 
		assign(array,cal,size);
		j=clock();
		qsort(cal,size,sizeof(int),compare);
		k=clock();
		qsort_time += k-j;
		for(a=0;a<size;a++)
		{
			outputD<<cal[a]<<endl;
		}
		
		//內建 sort 
		assign(array,cal,size);
		j=clock();
		sort(cal,cal+size);
		k=clock();
		sort_time += k-j;
		for(a=0;a<size;a++)
		{
			outputE<<cal[a]<<endl;
		}
		
		cout<<"Insertion Sort time:"<<insertion_sort_time<<endl;
		cout<<"merge Sort time:"<<merge_sort_time<<endl;
		cout<<"quick Sort time:"<<quick_sort_time<<endl;
		cout<<"內建 quick Sort time:"<<qsort_time<<endl;
		cout<<"內建 Sort time:"<<sort_time<<endl;
		cout<<"============================"<<endl;
	}
	cout<<"<總時間>"<<endl;
	cout<<"Insertion Sort time:"<<insertion_sort_time/10<<endl;
	cout<<"merge Sort time:"<<merge_sort_time/10<<endl;
	cout<<"quick Sort time:"<<quick_sort_time/10<<endl;
	cout<<"內建 quick Sort time:"<<qsort_time/10<<endl;
	cout<<"內建 Sort time:"<<sort_time/10<<endl;
	input.close();
	outputA.close();
	outputB.close();
	outputC.close();
	outputD.close();
	outputE.close();
}


