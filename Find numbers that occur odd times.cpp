//劉期正 B103040023 
//November. 12, 2022 
//給予一串數字，找出所有出現次數為奇數之數字
#include<iostream>
#include<stdlib.h>
#include<iomanip>
using namespace std;

class node 
{
	public:
		node(){right=0;left=0;};
		node(int a):data(a),left(0),right(0){};
		friend class tree; 
	private:
		int data;
		node *right;
		node *left;
};

class tree //用來存放每一個node 
{
	public:
		tree(){root=0;};
		node *root;
		
		void insert(int);//新增node 
		void del(node *c,int a);//若有相同的,則刪除 
		void leaf(node *c,int a);//刪除中,沒有son的 
		void noleaf(node *c,int a);//刪除中,僅有一個son 
		
		void printNode(node *c);//印node 
		void printLeft(node *c);//印Left
		void printRight(node *c);//印Right
};

void tree::insert(int a)
{
	if(root==0)//如果tree是空的,則直接新增 
		root=new node(a);
	else
	{
		node *current=root;
		bool same=false;
		
		while(1)//尋找對應的位置 
		{
			if(current->data==a)//判斷是否有相同數值 
			{
				same=true;
				break;
			}
			else if(a<current->data)//小的在左邊 
			{
				if(current->left)
					current=current->left;
				else
					break;
			}
			else if(a>current->data)//大的在右邊 
			{
				if(current->right)
					current=current->right;
				else
					break;
			}
		}
		
		if(same)//有相同則要刪除 
			del(current,a);
		else//沒相同則新增 
		{
			node *temp=new node(a);
			if(a<current->data)//小的新增在左邊 
				current->left=temp; 
			else if(a>current->data)//大的新增在右邊 
				current->right=temp;
		} 
	}
}

void tree::del(node *c,int a)
{
	if(c->left==0 && c->right==0)//沒有son 
		leaf(c,a);
	else if((c->left==0 && c->right!=0)||(c->left!=0 && c->right==0))//只有一個son 
		noleaf(c,a);
	else//有兩個son 
	{
		node *s=c->right;//right subtree中最左邊的 
		while(s->left)
			s=s->left; 
		a=s->data;//把取代欲刪除的 
		
        if(s->right==0)//看 right subtree中最左邊的node有沒有right 
			leaf(s,s->data);
		else
			noleaf(s,s->data);
		c->data=a;
	}
}

void tree::leaf(node *c,int a)
{
	node *temp=root;
	if(c==root)
		root=0;
	else
	{
		while(1)//尋找欲刪除node的parent 
		{
			if(temp->left==c || temp->right==c)
				break;
				
			if(a<temp->data)
				temp=temp->left;
			else if(a>temp->data)
				temp=temp->right;
		}
		
		if(a > temp->data)//較大的放右邊 
			temp->right=0;
		else if(a < temp->data)//較小放左邊 
			temp->left=0;
	}
	delete c;
}

void tree::noleaf(node *c,int a)
{
	if(c==root)//刪除的為root 
	{
		if(c->left)//左邊有東西則左邊變為root 
			root=c->left;
		else 
			root=c->right;
	}
	else
	{
		node *temp=root;
		while(1)//尋找對應位置 
		{
			if(temp->left==c || temp->right==c) 
				break;
				
			if(a>temp->data) 
				temp=temp->right;
			else if(a<temp->data)
				temp=temp->left;
		}
		
		if(a>temp->data)//接上欲刪除之node的parent 
		{
			if(c->left)
				temp->right=c->left;
			else
				temp->right=c->right;
		}
		else if(a<temp->data)
		{
			if(c->left)
				temp->left=c->left;
			else
				temp->left=c->right;
		}
	}
	delete c;	
}

void tree::printNode(node *c)//印node
{
	if(root==0)
		cout<<setw(3)<<"0";
	if(c)
	{
		printNode(c->left);
		cout<<setw(3)<<c->data;
		printNode(c->right);
	}
}

void tree::printLeft(node *c)//印left
{
	if(root==0)
		cout<<setw(3)<<"0";
	if(c)
	{
		printLeft(c->left);
		if(c->left)
			cout<<setw(3)<<c->left->data;
		else
			cout<<setw(3)<<"0";
		printLeft(c->right);
	}
}

void tree::printRight(node *c)//印right
{
	if(root==0)
		cout<<" 0";
	if(c)
	{
		printRight(c->left);
		if(c->right)
			cout<<setw(3)<<c->right->data;
		else
			cout<<setw(3)<<"0";
		printRight(c->right);
	}
}

int main()
{
	while(1)
	{
		int data;
		tree t;
		
		while(cin>>data)//讀取資料 
		{
			if(data==-1)
				break;
			else
				t.insert(data);//新增到tree中 
		}
		
		cout<<"node: ";//輸出 
		t.printNode(t.root);
		cout<<endl;
		
		cout<<"left: ";
		t.printLeft(t.root);
		cout<<endl;
		
		cout<<"right:";
		t.printRight(t.root);
		cout<<endl;
		
		cout<<endl;
	}
}
